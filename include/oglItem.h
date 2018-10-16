#ifndef OGL_TRIANGLE_INCLUDED
#define OGL_TRIANGLE_INCLUDED

#include <memory>
#include <QQuickItem>
#include <QQuickWindow>
#include "triangleRenderer.h"

/* TODO it will NOT update itself
 * by update I mean render at 30 FPS
 *
 * To enable such update, use QTimer or similar thing
 * TODO create update Q_INVOKABLE
 */
class OglItem : public QQuickItem {
    Q_OBJECT

/* Members */
private:
    std::unique_ptr<TriangleRenderer> m_renderer;


/* Methods */
public:
    static void registerQmlType();
    OglItem(QQuickItem *parent = nullptr);


/* Slots */
public slots:
    void sync();
    void cleanup();
private slots:
    void handleWindowChanged(QQuickWindow *win);

};

#endif //OGL_TRIANGLE_INCLUDED 
