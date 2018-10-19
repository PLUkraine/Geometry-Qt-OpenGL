#include "triangleRenderer.h"


#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QDebug>

TriangleRenderer::TriangleRenderer()
    : m_program(nullptr),
      m_window(nullptr)
{
    initGL();
}

void TriangleRenderer::setViewportSize(const QSize &size)
{
    m_viewportSize = size;
}

void TriangleRenderer::setWindow(QQuickWindow *window)
{
    m_window = window;
}

void TriangleRenderer::paint()
{
    QOpenGLExtraFunctions *ogl = QOpenGLContext::currentContext()->extraFunctions();

    qDebug() << "Paint Triangle Renderer";
    ogl->glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    ogl->glClearColor(1, 1, 1, 1);
    ogl->glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_vao.bind();

    ogl->glDrawArrays(GL_POINTS, 0, 3);

    m_vao.release();
    m_program->release();

    m_window->resetOpenGLState();
}

void TriangleRenderer::initGL()
{
    QOpenGLExtraFunctions *ogl = QOpenGLContext::currentContext()->extraFunctions();

    printVersionInformation(ogl);
    initProgram(ogl);
    initVAO(ogl);
}

void TriangleRenderer::initProgram(QOpenGLExtraFunctions *ogl)
{
    m_program.reset(new QOpenGLShaderProgram());

    // add vertex shader
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                ":/shaders/vert.glsl");
    // add fragment shader
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                ":/shaders/frag.glsl");
    m_program->link();
}

void TriangleRenderer::initVAO(QOpenGLExtraFunctions *ogl)
{

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };


    m_program->bind();
    Q_ASSERT(m_vao.create());
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    m_vbo.allocate(vertices, sizeof(vertices));
    m_program->enableAttributeArray(0);
    qDebug() << ogl->glGetError() << sizeof(vertices);

    ogl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);



    m_vbo.release();

    m_vao.release();
    m_program->release();
}

void TriangleRenderer::printVersionInformation(QOpenGLExtraFunctions *ogl)
{
    QString glType;
    QString glVersion;

    // Get Version Information
    glType = "OpenGL";
    glVersion = reinterpret_cast<const char*>(ogl->glGetString(GL_VERSION));

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion);
}
