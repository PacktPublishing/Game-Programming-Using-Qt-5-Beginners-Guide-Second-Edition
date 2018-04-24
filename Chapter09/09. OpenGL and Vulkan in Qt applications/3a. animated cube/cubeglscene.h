#ifndef CUBEGLSCENE_H
#define CUBEGLSCENE_H

#include <QImage>
#include "abstractglscene.h"
#include <QVector3D>
#include <QVector2D>
#include <QObject>

class QOpenGLTexture;
class SceneGLWindow;
class CubeGLScene : public QObject, public AbstractGLScene
{
    Q_OBJECT
    Q_PROPERTY(float angle READ angle WRITE setAngle)
public:
    CubeGLScene(SceneGLWindow *window);
    ~CubeGLScene();

    void initialize();
    void paint();
    void setTexture(const QImage &image);

    float angle() const;
    void setAngle(float angle);

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
    float m_angle;
};

#endif // CUBEGLSCENE_H
