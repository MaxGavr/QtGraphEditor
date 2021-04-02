#pragma once

#include <QGraphicsLineItem>
#include <QApplication>

#include "graphicsnodeitem.h"
#include "graph/graphedge.h"


class GraphicsEdgeItem : public QGraphicsLineItem
{
    Q_DECLARE_TR_FUNCTIONS(Edge)
public:
    GraphicsEdgeItem(GraphicsNodeItem* begin, GraphicsNodeItem* end, const GraphModel::Edge& edge);
    ~GraphicsEdgeItem();

    enum { Type = UserType + 1 };

    inline int type() const
    {
        return Type;
    }

    const GraphModel::Edge& getGraphEdge() const;
    bool isOriented() const;
    bool isLoop() const;

    GraphicsNodeItem* getStartNodeItem();
    GraphicsNodeItem* getEndNodeItem();

    void trackNodes();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QPen getDefaultPen();

private:
    QPointF calcLabelPosition() const;
    QPointF calcLoopPosition() const;

    QPen defaultPen;
    QGraphicsSimpleTextItem* label;

    GraphicsNodeItem* startNodeItem;
    GraphicsNodeItem* endNodeItem;

    QPolygonF arrowHead;
    QGraphicsEllipseItem* loop;

    static const int ARROW_SIZE;
    static const QSizeF loopSize;

    GraphModel::Edge::const_ref graphEdge;
};
