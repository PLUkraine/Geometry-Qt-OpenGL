#include <QGuiApplication>
#include <QQuickView>

#include "oglTriangle.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    OglTriangle::registerQmlType();

    QQuickView view;
    view.setTitle("Opengl Test");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
