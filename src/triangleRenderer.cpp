#include "triangleRenderer.h"
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
    if (!m_program) {
        initializeOpenGLFunctions();
        m_program.reset(new QOpenGLShaderProgram());
    }

    qDebug() << "Paint Triangle Renderer";
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_window->resetOpenGLState();
}
