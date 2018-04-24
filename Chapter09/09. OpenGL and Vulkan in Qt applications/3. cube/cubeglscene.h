#ifndef CUBEGLSCENE_H
#define CUBEGLSCENE_H

#include <QImage>
#include "abstractglscene.h"
#include <QVector3D>
#include <QVector2D>

class QOpenGLTexture;
class SceneGLWindow;
class CubeGLScene : public AbstractGLScene
{
public:
    CubeGLScene(SceneGLWindow *window);
    ~CubeGLScene();

    void initialize();
    void paint();
    void setTexture(const QImage &image);

protected:
    void initializeTexture();
    void initializeCubeData();
    void paintCube();

private:
    QImage m_textureImage;
    QOpenGLTexture* m_texture = nullptr;
    bool m_initialized = false;

    struct TexturedPoint {
        QVector3D coord;
        QVector2D uv;
        TexturedPoint(const QVector3D& pcoord = QVector3D(),
                      const QVector2D& puv = QVector2D()) :
            coord(pcoord), uv(puv) {
        }
    };

    QVector<TexturedPoint> m_data;
};

#endif // CUBEGLSCENE_H
