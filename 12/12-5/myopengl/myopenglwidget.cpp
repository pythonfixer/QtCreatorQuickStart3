#include "myopenglwidget.h"
#include <QOpenGLShaderProgram>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):
    QOpenGLWidget(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc = "in vec4 vPosition;                   \n"
                       "in vec4 vColor;                      \n"
                       "out vec4 color;                      \n"
                       "uniform mat4 matrix;                 \n"
                       "void main()                          \n"
                       "{                                    \n"
                       "    color = vColor;                  \n"
                       "    gl_Position = matrix * vPosition;\n"
                       "}                                    \n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc = "in vec4 color;     \n"
                       "out vec4 fColor;   \n"
                       "void main()        \n"
                       "{                  \n"
                       "    fColor = color;\n"
                       "}                  \n";
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

    GLfloat colors[2][4][3] = {
        {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
        {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}
    };
    vbo.write(24 * sizeof(GLfloat), colors, 24 * sizeof(GLfloat));
    GLuint vColor = program->attributeLocation("vColor");
    program->setAttributeBuffer(vColor, GL_FLOAT, 24 * sizeof(GLfloat), 3, 0);
    glEnableVertexAttribArray(vColor);

    QMatrix4x4 matrix;
    matrix.perspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    matrix.translate(0, 0, -3);
    matrix.rotate(-60, 0, 1, 0);
    program->setUniformValue("matrix", matrix);

    for (int i=0; i<2; i++)
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
}
