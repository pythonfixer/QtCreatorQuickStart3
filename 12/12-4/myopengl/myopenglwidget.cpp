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
    const char *vsrc = "in vec4 vPosition;          \n"
                       "in vec4 vColor;             \n"
                       "out vec4 color;             \n"
                       "void main()                 \n"
                       "{                           \n"
                       "    color = vColor;         \n"
                       "    gl_Position = vPosition;\n"
                       "}                           \n";
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

    GLfloat vertices[] = {
        -0.8f, 0.8f,
        -0.8f, -0.8f,
        0.8f, -0.8f,
        0.8f, 0.8f
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, 20 * sizeof(GLfloat));

    GLuint vPosition = program->attributeLocation("vPosition");
    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 2, 0);
    glEnableVertexAttribArray(vPosition);

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };
    vbo.write(8 * sizeof(GLfloat), colors, 12 * sizeof(GLfloat));
    GLuint vColor = program->attributeLocation("vColor");
    program->setAttributeBuffer(vColor, GL_FLOAT, 8 * sizeof(GLfloat), 3, 0);
    glEnableVertexAttribArray(vColor);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
