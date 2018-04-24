#include "cubeglscene.h"
#include <QOpenGLTexture>
#include <QOpenGLWindow>
#include "sceneglwindow.h"

CubeGLScene::CubeGLScene(SceneGLWindow *window) : AbstractGLScene(window)
{
    initializeCubeData();
}

CubeGLScene::~CubeGLScene()
{
  if (window()) {
      window()->makeCurrent();
  }
  delete m_texture;
}

void CubeGLScene::initialize()
{
    AbstractGLScene::initialize();
    m_initialized = true;
    if(!m_textureImage.isNull()) {
        initializeTexture();
    }
    glClearColor(1, 1, 1, 0);
    glShadeModel(GL_SMOOTH);
}

void CubeGLScene::paint()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window()->width(), window()->height());
    glLoadIdentity();

    glRotatef(45, 1.0, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    paintCube();
}

void CubeGLScene::setTexture(const QImage &image)
{
    m_textureImage = image;
    if(m_initialized) {
        initializeTexture();
    }
}

void CubeGLScene::initializeTexture()
{
    m_texture = new QOpenGLTexture(m_textureImage.mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void CubeGLScene::initializeCubeData()
{
    m_data = {
        // FRONT FACE
        {{-0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5,  0.5}, {0, 1}},

        // TOP FACE
        {{-0.5,  0.5,  0.5}, {0, 0}},        {{ 0.5,  0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        // BACK FACE
        {{-0.5,  0.5, -0.5}, {0, 0}},        {{ 0.5,  0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5, -0.5}, {1, 1}},        {{-0.5, -0.5, -0.5}, {0, 1}},

         // BOTTOM FACE
        {{-0.5, -0.5, -0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5,  0.5}, {1, 1}},        {{-0.5, -0.5,  0.5}, {0, 1}},

        // LEFT FACE
        {{-0.5, -0.5, -0.5}, {0, 0}},        {{-0.5, -0.5,  0.5}, {1, 0}},
        {{-0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        // RIGHT FACE
        {{ 0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{ 0.5,  0.5,  0.5}, {0, 1}},
    };
}

void CubeGLScene::paintCube()
{
    if(m_texture) {
        m_texture->bind();
    }
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for(const TexturedPoint &point: m_data) {
        glTexCoord2d(point.uv.x(), point.uv.y());
        glVertex3f(point.coord.x(), point.coord.y(), point.coord.z());
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

