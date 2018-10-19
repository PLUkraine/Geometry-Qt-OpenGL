#include <QGuiApplication>
#include <QQuickView>

#include <QSurfaceFormat>
#include <QOpenGLContext>

#include "OpenGlPlugin/oglItem.h"

void setSurfaceFormat() {
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);

    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    fmt.setSwapBehavior(QSurfaceFormat::DoubleBuffer);

    QSurfaceFormat::setDefaultFormat(fmt);
}

void registerTypes() {
    OglItem::registerQmlType();
}

int main(int argc, char *argv[])
{
    setSurfaceFormat();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    registerTypes();

    QQuickView view;
    view.setTitle("Opengl Test");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
