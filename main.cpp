#include <QGuiApplication>
#include <QQuickView>

#include <QSurfaceFormat>
#include <QOpenGLContext>

#include "oglItem.h"

void setSurfaceFormat() {
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);

    // Request OpenGL 3.3 compatibility or OpenGL ES 3.0.
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        fmt.setVersion(3, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        fmt.setVersion(3, 0);
    }

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
