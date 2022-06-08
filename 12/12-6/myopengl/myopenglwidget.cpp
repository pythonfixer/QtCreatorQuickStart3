#include "myopenglwidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):
    QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    for (int i = 0; i < 2; ++i)
        textures[i] = new QOpenGLTexture(QImage(QString("../myopengl/side%1.png").arg(i + 1)).mirrored());

    initializeOpenGLFunctions();

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc = "in vec4 vPosition;                   \n"
                       "in vec2 vTexCoord;                   \n"
                       "out vec2 texCoord;                   \n"
                       "uniform mat4 matrix;                 \n"
                       "void main()                          \n"
                       "{                                    \n"
                       "    texCoord = vTexCoord;            \n"
                       "    gl_Position = matrix * vPosition;\n"
                       "}                                    \n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc = "uniform sampler2D tex;              \n"
                       "in vec2 texCoord;                   \n"
                       "out vec4 fColor;                    \n"
                       "void main()                         \n"
                       "{                                   \n"
                       "    fColor = texture(tex, texCoord);\n"
                       "}                                   \n";
    fshader->compileSourceCode(fsrc);

    program = new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);
    program->link();
    program->bind();
}

void MyOpenGLWidget::resizeGL(int, int)
{

}

void MyOpenGLWidget::paintGL()
{
    int w = width();
    int h = height();
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat vertices[2][4][3] = {
        {{-0.8f, 0.8f, 0.8f}, {-0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, 0.8f, 0.8f}},
        {{0.8f, 0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, -0.8f}, {0.8f, 0.8f, -0.8f}}
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, 48 * sizeof(GLfloat));

    GLuint vPosition = program->attributeLocation("vPosition");
    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
    glEnableVertexAttribArray(vPosition);

    GLfloat coords[2][4][2] = {
        {{0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}
    };
    vbo.write(24 * sizeof(GLfloat), coords, 16 * sizeof(GLfloat));
    GLuint vTexCoord = program->attributeLocation("vTexCoord");
    program->setAttributeBuffer(vTexCoord, GL_FLOAT, 24 * sizeof(GLfloat), 2, 0);
    glEnableVertexAttribArray(vTexCoord);
    program->setUniformValue("tex", 0);

    QMatrix4x4 matrix;
    matrix.perspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    matrix.translate(0, 0, -3);
    matrix.rotate(-60, 0, 1, 0);
    program->setUniformValue("matrix", matrix);

    for (int i=0; i<2; i++)
    {
        textures[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
}
