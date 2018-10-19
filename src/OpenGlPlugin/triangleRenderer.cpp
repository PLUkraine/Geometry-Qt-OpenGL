#include "OpenGlPlugin/triangleRenderer.h"


#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QDebug>


void _check_gl_error(const char *file, int line) {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    GLenum err (f->glGetError());

    while (err != GL_NO_ERROR) {
        std::string error;

        switch(err) {
            case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
            case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }

        qDebug() << "GL" << error.c_str() <<"-"<<file<<":"<<line;
        err = f->glGetError();
    }
}


TriangleRenderer::TriangleRenderer()
    : m_program(nullptr),
      m_window(nullptr)
{
    initGL();
}

TriangleRenderer::~TriangleRenderer()
{
    /*
     * This makes apap crash!!!
     * Do NOT getFunctions inside of the destructor.
     * It crashed the app
     */
//    auto ogl = getFunctions();

//    ogl->glDeleteBuffers(1, &m_posVbo);
//    ogl->glDeleteBuffers(1, &m_colVbo);
//    ogl->glDeleteVertexArrays(1, &m_vao);
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
    QOpenGLExtraFunctions *ogl = getFunctions();

    qDebug() << "Paint Triangle Renderer";
    ogl->glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    ogl->glClearColor(1, 1, 1, 1);
    ogl->glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    ogl->glBindVertexArray(m_vao);
    check_gl_error();

    ogl->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    check_gl_error();

    ogl->glBindVertexArray(0);
    m_program->release();

    m_window->resetOpenGLState();
}

QOpenGLExtraFunctions *TriangleRenderer::getFunctions() const
{
    return QOpenGLContext::currentContext()->extraFunctions();
}

void TriangleRenderer::initGL()
{
    initProgram();
    initVAO();
}

void TriangleRenderer::initProgram()
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

void TriangleRenderer::initVAO()
{
    auto ogl = getFunctions();
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left bottom
         0.5f, -0.5f, 0.0f, // right bottom
         0.5f,  0.5f, 0.0f, // top right
        -0.5f,  0.5f, 0.0f, // top left
    };
    GLfloat colors[] = {
         1.0f,  0.0f, 0.0f, // left
         0.0f,  1.0f, 0.0f, // right
         0.0f,  0.0f, 1.0f, // top
         1.0f,  1.0f, 0.0f, // top
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
    };


    m_program->bind();
    ogl->glGenVertexArrays(1, &m_vao);
    ogl->glGenBuffers(1, &m_posVbo);
    ogl->glGenBuffers(1, &m_colVbo);
    ogl->glGenBuffers(1, &m_ebo);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    ogl->glBindVertexArray(m_vao);

    ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    ogl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    ogl->glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
    ogl->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ogl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    ogl->glEnableVertexAttribArray(0);

    ogl->glBindBuffer(GL_ARRAY_BUFFER, m_colVbo);
    ogl->glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    ogl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    ogl->glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    ogl->glBindVertexArray(0);

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
