#ifndef OGL_TRIANGLE_INCLUDED
#define OGL_TRIANGLE_INCLUDED

#include <QQuickItem>
#include <QQuickWindow>

class OglTriangle : public QQuickItem {

public:
    static void registerQmlType();
    OglTriangle(QQuickItem *parent = nullptr);

//public slots:
//    void sync();
//    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

};

#endif //OGL_TRIANGLE_INCLUDED 
