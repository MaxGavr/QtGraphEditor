#include "graphicsedgeitem.h"

GraphicsEdgeItem::GraphicsEdgeItem(GraphicsNodeItem* begin, GraphicsNodeItem* end, const GraphEdge &edge)
    : graphEdge(edge)
{
    startNodeItem = begin;
    endNodeItem = end;

    startNodeItem->addEdgeItem(this);
    endNodeItem->addEdgeItem(this);

    setFlags(ItemIsSelectable);
    setPen(QPen(Qt::darkGray, 3));
    setZValue(-1);

    trackNodes();
}

GraphicsEdgeItem::~GraphicsEdgeItem()
{
    getStartNodeItem()->removeEdgeItem(this);
    getEndNodeItem()->removeEdgeItem(this);
}

const GraphEdge& GraphicsEdgeItem::getGraphEdge() const
{
    return graphEdge;
}


GraphicsNodeItem* GraphicsEdgeItem::getStartNodeItem()
{
    return startNodeItem;
}

GraphicsNodeItem* GraphicsEdgeItem::getEndNodeItem()
{
    return endNodeItem;
}


void GraphicsEdgeItem::trackNodes()
{
    setLine(QLineF(startNodeItem->getCenterPos(), endNodeItem->getCenterPos()));
}
