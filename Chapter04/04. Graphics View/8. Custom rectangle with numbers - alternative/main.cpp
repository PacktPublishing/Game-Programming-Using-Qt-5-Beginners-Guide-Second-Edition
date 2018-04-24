#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>

QGraphicsRectItem *createComplexItem(qreal width, qreal height, qreal radius) {
    QRectF rect(-width / 2, -height / 2, width, height);
    rect.translate(0.5, 0.5);
    QGraphicsRectItem *parent = new QGraphicsRectItem(rect);
    QPen pen = parent->pen();
    pen.setCosmetic(true);
    parent->setPen(pen);

    QRectF circleBoundary(-radius, -radius, 2 * radius, 2 * radius);
    for(int i = 0; i < 4; i++) {
        QGraphicsEllipseItem *child =
                new QGraphicsEllipseItem(circleBoundary, parent);
        child->setBrush(Qt::black);
        QPointF pos;
        switch(i) {
        case 0:
            pos = rect.topLeft();
            break;
        case 1:
            pos = rect.bottomLeft();
            break;
        case 2:
            pos = rect.topRight();
            break;
        case 3:
            pos = rect.bottomRight();
            break;
        }
        child->setPos(pos);

        QGraphicsSimpleTextItem *text =
                new QGraphicsSimpleTextItem(QString::number(i), child);
        text->setBrush(Qt::green);
        QTransform transform;
        transform.translate(-text->boundingRect().width() / 2,
                            -text->boundingRect().height() / 2);
        text->setTransform(transform);
        text->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }
    return parent;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    QGraphicsRectItem *item1 = createComplexItem(100, 60, 8);
    scene.addItem(item1);

    QGraphicsRectItem *item2 = createComplexItem(100, 60, 8);
    scene.addItem(item2);
    item2->setPos(200, 0);
    item2->setRotation(20);

    QGraphicsView view(&scene);
    view.resize(800, 600);
    view.show();
    view.setRenderHint(QPainter::Antialiasing);
    view.scale(2, 2);

    return a.exec();
}

