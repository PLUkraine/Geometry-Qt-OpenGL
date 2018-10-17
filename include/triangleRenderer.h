#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <memory>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>

class TriangleRenderer : public QObject {
    Q_OBJECT

/* Members */
private:
    QSize m_viewportSize;
    std::unique_ptr<QOpenGLShaderProgram> m_program;
    QQuickWindow *m_window;

public:
    TriangleRenderer();
    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);

public slots:
    void paint();
};

#endif //TRIANGLE_RENDERER
