#pragma once
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QList>
#include <QMessageBox>

class Edge;

class Node : public QGraphicsEllipseItem
{
public:
    Node(const QPointF& position);

    enum { Type = UserType + 1 };

    int type() const
    {
        return Type;
    }

    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);

    QPointF getCenterPos() const;
    void setCenterPos(qreal x, qreal y);

private:
    QList<Edge*> edges;

    const int NODE_DIAMETER = 20;
};
