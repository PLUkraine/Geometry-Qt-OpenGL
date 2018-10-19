#include "OpenGlPlugin/oglItem.h"

#include <QDebug>

void OglItem::renderOgl()
{
    if (window()) {
        window()->update();
    }
}

void OglItem::registerQmlType()
{
    qmlRegisterType<OglItem>("OpenGlPlugin", 1, 0, "OglItem");
}

OglItem::OglItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    connect(this, &QQuickItem::windowChanged, this, &OglItem::handleWindowChanged);
}

void OglItem::sync()
{
    if (!m_renderer) {
        qDebug() << "Create New Renderer";
        m_renderer.reset(new TriangleRenderer());
        connect(window(), &QQuickWindow::beforeRendering, m_renderer.get(), &TriangleRenderer::paint, Qt::DirectConnection);
    }

    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setWindow(window());
}

void OglItem::cleanup()
{
    qDebug() << "Scene Graph Invalidated";
    m_renderer.reset(nullptr);
}

void OglItem::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &OglItem::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &OglItem::cleanup, Qt::DirectConnection);

        win->setClearBeforeRendering(false);
    }
}
