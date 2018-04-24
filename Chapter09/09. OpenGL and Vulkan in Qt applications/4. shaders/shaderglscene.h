#ifndef SHADERGLSCENE_H
#define SHADERGLSCENE_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include "abstractglscene.h"
#include "sceneglwindow.h"

class ShaderGLScene : public QObject, public AbstractGLScene {
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle WRITE setAngle)
public:
    ShaderGLScene(SceneGLWindow *window);
    void initialize();
    void paint();

    qreal angle() const;
    void paintObject(const QMatrix4x4& mvMatrix);

public slots:
        void setAngle(qreal a);

protected:
    void initializeCubeData();

private:
    bool m_initialized;
    qreal m_angle = 0;

    struct ScenePoint {
        QVector3D coords;
        QVector3D normal;

        ScenePoint(const QVector3D &c = QVector3D(),
                   const QVector3D &n = QVector3D()) :
            coords(c), normal(n)
        {

        }
    };

    QVector<ScenePoint> m_data;
    QOpenGLShaderProgram m_shader;

    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;

};

#endif // SHADERGLSCENE_H
