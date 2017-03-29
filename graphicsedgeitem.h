#pragma once

#include <QGraphicsLineItem>
#include <QApplication>

#include "graphicsnodeitem.h"

class GraphicsEdgeItem : public QGraphicsLineItem
{
    Q_DECLARE_TR_FUNCTIONS(Edge)
public:
    GraphicsEdgeItem(GraphicsNodeItem* begin, GraphicsNodeItem* end, const GraphEdge& edge);
    ~GraphicsEdgeItem();

    enum { Type = UserType + 1 };

    inline int type() const
    {
        return Type;
    }

    const GraphEdge& getGraphEdge() const;

    GraphicsNodeItem* getStartNodeItem();
    GraphicsNodeItem* getEndNodeItem();

    void trackNodes();

private:
    GraphicsNodeItem* startNodeItem;
    GraphicsNodeItem* endNodeItem;

    const GraphEdge& graphEdge;
};
