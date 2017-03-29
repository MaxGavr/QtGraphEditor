#pragma once
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QList>

#include "graph/graphnode.h"

class GraphicsEdgeItem;

class GraphicsNodeItem : public QGraphicsEllipseItem
{
public:
    GraphicsNodeItem(const QPointF& position, const GraphNode& node);
    ~GraphicsNodeItem();

    enum { Type = UserType + 2 };

    inline int type() const
    {
        return Type;
    }

    const GraphNode& getGraphNode() const;

    void addEdgeItem(GraphicsEdgeItem* edgeItem);
    void removeEdgeItem(GraphicsEdgeItem* edgeItem);

    QPointF getCenterPos() const;
    void setCenterPos(qreal x, qreal y);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    const GraphNode& graphNode;

    QList<GraphicsEdgeItem*> edges;

    const int NODE_DIAMETER = 20;
};
