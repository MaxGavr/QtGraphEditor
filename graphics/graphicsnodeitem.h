#pragma once
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QPainter>

#include "graph/graphnode.h"

class GraphicsEdgeItem;


class GraphicsNodeItem : public QGraphicsEllipseItem
{
public:
    GraphicsNodeItem(const QPointF& position, const GraphModel::Node& node);
    ~GraphicsNodeItem();

    enum { Type = UserType + 2 };

    inline int type() const
    {
        return Type;
    }

    static const int NODE_DIAMETER;

    const GraphModel::Node& getGraphNode() const;
    QList<GraphicsEdgeItem*> getEdgeItems();

    void addEdgeItem(GraphicsEdgeItem* edgeItem);
    void removeEdgeItem(GraphicsEdgeItem* edgeItem);

    QPointF getCenterPos() const;
    void setCenterPos(qreal x, qreal y);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPen getDefaultPen() const;
    QBrush getDefaultBrush() const;

private:
    QPointF calcLabelPosition() const;

    const GraphModel::Node& graphNode;

    QList<GraphicsEdgeItem*> edges;
    QGraphicsSimpleTextItem* label;

    QPen defaultPen;
    QBrush defaultBrush;
};
