#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <memory>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLDebugLogger>
#include <QOpenGLBuffer>

class TriangleRenderer : public QObject {
    Q_OBJECT

/* Members */
private:
    QSize m_viewportSize;
    std::unique_ptr<QOpenGLShaderProgram> m_program;
    QQuickWindow *m_window;

    // TODO put in the model
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

public:
    TriangleRenderer();
    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);

public slots:
    void paint();

private:
    void initGL();
    void initProgram(QOpenGLExtraFunctions *ogl);
    void initVAO(QOpenGLExtraFunctions *ogl);
    void printVersionInformation(QOpenGLExtraFunctions *ogl);
};

#endif //TRIANGLE_RENDERER
