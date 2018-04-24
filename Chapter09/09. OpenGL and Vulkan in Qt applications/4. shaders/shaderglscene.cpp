#include "shaderglscene.h"
#include <QFile>
#include "plyreader.h"

ShaderGLScene::ShaderGLScene(SceneGLWindow *window) : AbstractGLScene(window) {
    window->setScene(this);
    m_initialized = false;
    initializeCubeData();
}

void ShaderGLScene::initialize() {
    AbstractGLScene::initialize();
    m_initialized = true;
    glClearColor(0, 0, 0, 0);

    m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/phong.vert");
    m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/phong.frag");
    m_shader.link();
    m_shader.bind();
    m_shader.setAttributeArray("Vertex", GL_FLOAT,
                               &m_data[0].coords, 3, sizeof(ScenePoint));
    m_shader.enableAttributeArray("Vertex");

    m_shader.setAttributeArray("Normal", GL_FLOAT,
                               &m_data[0].normal, 3, sizeof(ScenePoint));
    m_shader.enableAttributeArray("Normal");

    m_shader.setUniformValue("mat.ka", QVector3D(0.1, 0, 0.0));
    m_shader.setUniformValue("mat.kd", QVector3D(0.7, 0.0, 0.0));
    m_shader.setUniformValue("mat.ks", QVector3D(1.0, 1.0, 1.0));
    m_shader.setUniformValue("mat.shininess", 128.0f);

    m_shader.setUniformValue("light.position", QVector3D(2, 1, 1));
    m_shader.setUniformValue("light.intensity", QVector3D(1, 1, 1));
}

void ShaderGLScene::paint() {
    m_projectionMatrix.setToIdentity();
    float aspectRatio = qreal(window()->width()) / window()->height();
    m_projectionMatrix.perspective(90, aspectRatio, 0.5, 40);

    m_viewMatrix.setToIdentity();
    QVector3D eye(0, 0, 2);
    QVector3D center(0, 0, 0);
    QVector3D up(0, 1, 0);
    m_viewMatrix.lookAt(eye, center, up);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window()->width(), window()->height());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_modelMatrix.setToIdentity();
    m_modelMatrix.scale(2);
    m_modelMatrix.rotate(m_angle, 0, 1, 0);
    m_modelMatrix.rotate(-90, 1, 0, 0);

    QMatrix4x4 modelViewMatrix = m_viewMatrix * m_modelMatrix;
    paintObject(modelViewMatrix);
}

qreal ShaderGLScene::angle() const {
    return m_angle;
}

void ShaderGLScene::paintObject(const QMatrix4x4 &mvMatrix) {
    m_shader.bind();
    m_shader.setUniformValue("projectionMatrix", m_projectionMatrix);
    m_shader.setUniformValue("modelViewMatrix", mvMatrix);
    m_shader.setUniformValue("mvpMatrix", m_projectionMatrix*mvMatrix);
    m_shader.setUniformValue("normalMatrix", mvMatrix.normalMatrix());
    glDrawArrays(GL_TRIANGLES, 0, m_data.size());
}

void ShaderGLScene::setAngle(qreal a) {
    m_angle = a;
    window()->update();
}

void ShaderGLScene::initializeCubeData() {
    PlyReader reader(":/monkey.ply");
    if(reader.read()) {
        // reconstruct faces
        const QVector<PlyReader::ScenePoint> vertices = reader.vertices();
        const QVector<QVector<int>> faces = reader.faces();
        for(const QVector<int>& face: faces) {
            ScenePoint pt;
            for(int vertexId: face) {
                const PlyReader::ScenePoint &scenePoint = vertices.at(vertexId);
                pt.coords = scenePoint.coord;
                pt.normal = scenePoint.normal;
                m_data << pt;
            }
        }
    }
}
