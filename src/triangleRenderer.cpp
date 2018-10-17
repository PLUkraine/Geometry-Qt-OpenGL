#include "triangleRenderer.h"


#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QDebug>

TriangleRenderer::TriangleRenderer()
    : m_program(nullptr),
      m_window(nullptr)
{ }

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
    if (!m_program) {
        m_program.reset(new QOpenGLShaderProgram());
    }

    qDebug() << "Paint Triangle Renderer";
    f->glClearColor(0.5, 1, 1, 1);
    f->glClear(GL_COLOR_BUFFER_BIT);

    m_window->resetOpenGLState();
}
