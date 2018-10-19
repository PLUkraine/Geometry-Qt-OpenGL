#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <memory>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLDebugLogger>
#include <QOpenGLBuffer>

void _check_gl_error(const char *file, int line);
///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

class TriangleRenderer : public QObject {
    Q_OBJECT

/* Members */
private:
    QSize m_viewportSize;
    std::unique_ptr<QOpenGLShaderProgram> m_program;
    QQuickWindow *m_window;

    // TODO put in the model
    GLuint m_vao;
    GLuint m_posVbo;
    GLuint m_colVbo;
    GLuint m_ebo;

public:
    TriangleRenderer();
    ~TriangleRenderer();
    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);

public slots:
    void paint();

private:
    QOpenGLExtraFunctions *getFunctions() const;
    void initGL();
    void initProgram();
    void initVAO();
    void printVersionInformation(QOpenGLExtraFunctions *ogl);
};

#endif //TRIANGLE_RENDERER
