#include <QApplication>
#include "scene.h"
#include <QGraphicsView>
#include <QDateTime>
#include <QFile>
#include <QDebug>

QString loadFile(const QString& path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "failed to open " << path;
        return QString();
    }
    return QString::fromUtf8(file.readAll());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QDateTime::currentMSecsSinceEpoch());

    Scene scene;
    scene.setTeamSize(10);
    scene.setFieldSize(QSize(20, 20));
    scene.setStepDuration(1000);
    scene.setScript(0, loadFile(":/scripts/1.js"));
    scene.setScript(1, loadFile(":/scripts/2.js"));

    scene.start();
    QGraphicsView view(&scene);
    view.scale(20, 20);
    view.setRenderHint(QPainter::Antialiasing);
    view.show();
    return app.exec();
}
