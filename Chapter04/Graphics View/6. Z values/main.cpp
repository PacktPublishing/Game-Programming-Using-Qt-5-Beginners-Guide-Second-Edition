#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    QGraphicsEllipseItem *item1 = scene.addEllipse(0, 0, 100, 50);
    item1->setBrush(Qt::red);
    QGraphicsEllipseItem *item2 = scene.addEllipse(50, 0, 100, 50);
    item2->setBrush(Qt::green);
    QGraphicsEllipseItem *item3 = scene.addEllipse(0, 25, 100, 50);
    item3->setBrush(Qt::blue);
    QGraphicsEllipseItem *item4 = scene.addEllipse(50, 25, 100, 50);
    item4->setBrush(Qt::gray);

    item2->setZValue(1);

    QGraphicsView view(&scene);

    view.setRenderHint(QPainter::Antialiasing);
    view.show();

    return a.exec();
}

