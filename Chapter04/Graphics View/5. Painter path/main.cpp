#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    static const int SIZE = 100;
    static const int MARGIN = 10;
    static const int FIGURE_COUNT = 5;
    static const int LINE_COUNT = 500;
    for(int figureNum = 0; figureNum < FIGURE_COUNT; ++figureNum) {
        QPainterPath path;
        path.moveTo(0, 0);
        for(int i = 0; i < LINE_COUNT; ++i) {
            path.lineTo(qrand() % SIZE, qrand() % SIZE);
        }
        QGraphicsPathItem *item = scene.addPath(path);
        item->setPos(figureNum * (SIZE + MARGIN), 0);
    }

    QGraphicsView view(&scene);
    view.resize(800, 600);
    view.show();
    view.setRenderHint(QPainter::Antialiasing);

    return a.exec();
}

