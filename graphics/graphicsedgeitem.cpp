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

    label = new QGraphicsSimpleTextItem(QString::number(getGraphEdge().getWeight()), this);
    label->setFont(QFont("Helvetica", 12));

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

void GraphicsEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    label->setText(QString::number(getGraphEdge().getWeight()));
    label->setPos(calcLabelPosition());
    QGraphicsLineItem::paint(painter, option, widget);
}

QPointF GraphicsEdgeItem::calcLabelPosition() const
{
    QString text = QString::number(getGraphEdge().getWeight());
    QFontMetrics metrics(label->font());
    QPointF center = boundingRect().center();
    int x = center.x() - metrics.width(text)/2;
    int y = center.y() - metrics.height();
    return QPointF(x, y);
}
