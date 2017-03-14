#include "node.h"
#include "edge.h"

Node::Node(const QPointF& position)
{
    setRect(QRectF(0, 0, NODE_DIAMETER, NODE_DIAMETER));
    setCenterPos(position.x(), position.y());
    setPen(QPen(Qt::black, 3));
    setBrush(QBrush(Qt::lightGray));

    setFlags(ItemIsMovable | ItemIsSelectable);
}

void Node::addEdge(Edge *edge)
{
    if (edge && !edges.contains(edge))
        edges.append(edge);
}

void Node::removeEdge(Edge *edge)
{
    if (edge)
        edges.removeOne(edge);
}

QPointF Node::getCenterPos() const
{
    QPointF center;
    center.setX(scenePos().x() + NODE_DIAMETER/2);
    center.setY(scenePos().y() + NODE_DIAMETER/2);
    return center;
}

void Node::setCenterPos(qreal x, qreal y)
{
    qreal leftTopX = x - NODE_DIAMETER/2;
    qreal leftTopY = y - NODE_DIAMETER/2;

    leftTopX = leftTopX < 0 ? 0 : leftTopX;
    leftTopY = leftTopY < 0 ? 0 : leftTopY;

    setPos(leftTopX, leftTopY);
}
