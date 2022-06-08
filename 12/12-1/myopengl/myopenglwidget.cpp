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
    const char *vsrc = "void main()                                \n"
                       "{                                          \n"
                       "    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n"
                       "}                                          \n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc = "void main()                                 \n"
                       "{                                           \n"
                       "    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}                                           \n";
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
    glDrawArrays(GL_POINTS, 0, 1);
}
