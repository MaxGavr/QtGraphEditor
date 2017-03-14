#pragma once
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QList>

class Edge;

class Node : public QGraphicsEllipseItem
{
public:
    Node(QPointF position);

    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);

private:
    QList<Edge*> edges;
};
