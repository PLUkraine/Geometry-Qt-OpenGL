#include "triangleRenderer.h"


#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QDebug>

TriangleRenderer::TriangleRenderer()
    : m_program(nullptr),
      m_window(nullptr)
{
    initGL();
}

void TriangleRenderer::setViewportSize(const QSize &size)
{
    m_viewportSize = size;
}

void TriangleRenderer::setWindow(QQuickWindow *window)
{
    m_window = window;
}

void TriangleRenderer::paint()
{
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    qDebug() << "Paint Triangle Renderer";
    f->glClearColor(0.5, 1, 1, 1);
    f->glClear(GL_COLOR_BUFFER_BIT);

    m_window->resetOpenGLState();
}

void TriangleRenderer::initGL()
{
    QOpenGLExtraFunctions *ogl = QOpenGLContext::currentContext()->extraFunctions();

    initProgram();

}

void TriangleRenderer::initProgram()
{
    m_program.reset(new QOpenGLShaderProgram());

    // add vertex shader
    QFile vertShaderFile(":/shaders/vert.glsl");
    vertShaderFile.open(QIODevice::ReadOnly | QIODevice::Text);
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                                vertShaderFile.readAll());

    // add fragment shader
    QFile fragShaderFile(":/shaders/frag.glsl");
    fragShaderFile.open(QIODevice::ReadOnly | QIODevice::Text);
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                fragShaderFile.readAll());
    m_program->link();
}
