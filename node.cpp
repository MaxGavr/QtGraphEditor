#include "node.h"
#include "edge.h"

Node::Node(QPointF position)
{
    setRect(QRectF(position.x(), position.y(), 10, 10));
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
