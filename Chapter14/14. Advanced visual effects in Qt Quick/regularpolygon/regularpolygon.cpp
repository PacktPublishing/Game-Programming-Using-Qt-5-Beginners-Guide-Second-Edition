#include "regularpolygon.h"
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <cmath>

RegularPolygon::RegularPolygon()
{
    setFlag(ItemHasContents, true);
    m_vertexCount = 6;
}

RegularPolygon::~RegularPolygon() {

}

int RegularPolygon::vertices() const {
    return m_vertexCount; }

void RegularPolygon::setVertices(int v) {
    v = qMax(3, v);
    if(v == vertices()) return;
    m_vertexCount = v;
    emit verticesChanged(v);
    update();
}

QColor RegularPolygon::color() const {
    return m_color;
}

void RegularPolygon::setColor(const QColor &c) {
    if(color() == c) return;
    m_color = c;
    emit colorChanged(c);
    update();
}

QSGNode *RegularPolygon::updatePaintNode(
    QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(
            QSGGeometry::defaultAttributes_Point2D(), m_vertexCount + 2);
        geometry->setDrawingMode(GL_TRIANGLE_FAN);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_vertexCount + 2);
    }

    // verify material
    QSGMaterial *material = node->material();
    QSGFlatColorMaterial *flatMaterial =
            static_cast<QSGFlatColorMaterial*>(material);
    if(flatMaterial->color() != m_color) {
        flatMaterial->setColor(m_color);
        node->markDirty(QSGNode::DirtyMaterial);
    }

    QRectF bounds = boundingRect();
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    // first vertex is the shared one (middle)
    QPointF center = bounds.center();

    vertices[0].set(center.x(), center.y());

    // vertices are distributed along circumference of a circle

    qreal angleStep = 360.0 / m_vertexCount;

    qreal radius = qMin(width(), height()) / 2;

    for (int i = 0; i < m_vertexCount; ++i) {
        qreal rads = angleStep * i * M_PI / 180;
        qreal x = center.x()+radius*std::cos(rads);
        qreal y = center.y()+radius*std::sin(rads);
        vertices[1 + i].set(x, y);
    }
    vertices[1 + m_vertexCount] = vertices[1];
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}

