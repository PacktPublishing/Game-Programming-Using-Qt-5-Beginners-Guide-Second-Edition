#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    scene.addLine(-100, 0, 100, 0);
    scene.addLine(0, -100, 0, 100);

    int exampleNumber = 0;

    switch(exampleNumber) {
        case 0: {
            scene.addRect(50, 50, 50, 50);
            break;
        }
        case 1: {
            QGraphicsRectItem* rectItem = scene.addRect(50, 50, 50, 50);
            rectItem->setRotation(45);
            break;
        }
        case 2: {
            QGraphicsRectItem* rectItem = scene.addRect(50, 50, 50, 50);
            rectItem->setTransformOriginPoint(75, 75);
            rectItem->setRotation(45);
            break;
        }
        case 3: {
            QGraphicsRectItem* rectItem = scene.addRect(50, 50, 50, 50);
            rectItem->setTransformOriginPoint(75, 75);
            QTransform transform;
            transform.rotate(45);
            rectItem->setTransform(transform);
            break;
        }
        case 4: {
            QGraphicsRectItem* rectItem = scene.addRect(-25, -25, 50, 50);
            rectItem->setPos(75, 75);
            break;
        }
        case 5: {
            QGraphicsRectItem* rectItem = scene.addRect(-25, -25, 50, 50);
            rectItem->setPos(75, 75);
            rectItem->setRotation(45);
            break;
        }
    }

    QGraphicsView view(&scene);
    view.show();

    return a.exec();
}
