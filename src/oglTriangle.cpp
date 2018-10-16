#include "oglTriangle.h"

#include <QDebug>

void OglTriangle::registerQmlType()
{
    qmlRegisterType<OglTriangle>("OpenGlPlugin", 1, 0, "OglTriangle");
}

OglTriangle::OglTriangle(QQuickItem *parent)
    : QQuickItem(parent)
{
    connect(this, &QQuickItem::windowChanged, this, &OglTriangle::handleWindowChanged);
}

void OglTriangle::handleWindowChanged(QQuickWindow *win)
{
    qDebug() << "Window Changed";
}
