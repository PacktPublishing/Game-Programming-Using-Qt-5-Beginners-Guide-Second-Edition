#include <QGuiApplication>
#include <Qt3DWindow>
#include <QCamera>
#include <QForwardRenderer>
#include <QEntity>
#include <QCuboidMesh>
#include <QDiffuseSpecularMaterial>
#include <QTransform>
#include <QFirstPersonCameraController>
#include <QDirectionalLight>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    Qt3DExtras::Qt3DWindow window;
    window.defaultFrameGraph()->setClearColor(Qt::black);

    Qt3DRender::QCamera *camera = window.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 40.0f, -40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    Qt3DExtras::QFirstPersonCameraController *cameraController =
        new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    cameraController->setCamera(camera);

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QDirectionalLight *lightComponent = new Qt3DRender::QDirectionalLight();
    lightComponent->setColor(Qt::white);
    lightComponent->setIntensity(0.5);
    lightComponent->setWorldDirection(QVector3D(0, -1, 0));
    lightEntity->addComponent(lightComponent);

    Qt3DCore::QEntity *cubeEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCuboidMesh *cubeMesh = new Qt3DExtras::QCuboidMesh();
    Qt3DExtras::QDiffuseSpecularMaterial *cubeMaterial =
        new Qt3DExtras::QDiffuseSpecularMaterial();
    cubeMaterial->setAmbient(Qt::white);
    Qt3DCore::QTransform *cubeTransform = new Qt3DCore::QTransform();
    cubeTransform->setScale(10);
    cubeEntity->addComponent(cubeMesh);
    cubeEntity->addComponent(cubeMaterial);
    cubeEntity->addComponent(cubeTransform);

    window.setRootEntity(rootEntity);
    window.show();

    return app.exec();
}
