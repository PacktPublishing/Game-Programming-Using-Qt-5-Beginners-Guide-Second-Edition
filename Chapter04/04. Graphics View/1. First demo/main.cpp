#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    QGraphicsRectItem *rectItem = new QGraphicsRectItem(QRectF(0, 0, 100, 50));
    scene.addItem(rectItem);

    QGraphicsEllipseItem *circleItem =
            new QGraphicsEllipseItem(QRectF(0, 50, 25, 25));
    scene.addItem(circleItem);

    QGraphicsSimpleTextItem *textItem =
            new QGraphicsSimpleTextItem(QObject::tr("Demo"));
    scene.addItem(textItem);

    QGraphicsView view(&scene);
    view.show();
    return a.exec();
}
