#include "graphicsnodeitem.h"
#include "graphicsedgeitem.h"

GraphicsNodeItem::GraphicsNodeItem(const QPointF& position, const GraphNode &node)
    : graphNode(node)
{
    setRect(QRectF(0, 0, NODE_DIAMETER, NODE_DIAMETER));
    setCenterPos(position.x(), position.y());

    setPen(QPen(Qt::black, 3));
    setBrush(QBrush(Qt::lightGray));

    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);

    label = new QGraphicsSimpleTextItem(getGraphNode().getText(), this);
    label->setFont(QFont("Helvetica", 12));
}

GraphicsNodeItem::~GraphicsNodeItem()
{
    qDeleteAll(edges);
}

const GraphNode& GraphicsNodeItem::getGraphNode() const
{
    return graphNode;
}

QList<GraphicsEdgeItem *> GraphicsNodeItem::getEdgeItems()
{
    return edges;
}

void GraphicsNodeItem::addEdgeItem(GraphicsEdgeItem *edgeItem)
{
    if (edgeItem && !edges.contains(edgeItem))
        edges.append(edgeItem);
}

void GraphicsNodeItem::removeEdgeItem(GraphicsEdgeItem *edgeItem)
{
    if (edgeItem)
        edges.removeOne(edgeItem);
}

QPointF GraphicsNodeItem::getCenterPos() const
{
    QPointF center;
    center.setX(scenePos().x() + NODE_DIAMETER/2);
    center.setY(scenePos().y() + NODE_DIAMETER/2);
    return center;
}

void GraphicsNodeItem::setCenterPos(qreal x, qreal y)
{
    qreal leftTopX = x - NODE_DIAMETER/2;
    qreal leftTopY = y - NODE_DIAMETER/2;

    leftTopX = leftTopX < 0 ? 0 : leftTopX;
    leftTopY = leftTopY < 0 ? 0 : leftTopY;

    setPos(leftTopX, leftTopY);
}

QVariant GraphicsNodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
        foreach (GraphicsEdgeItem* edge, edges)
            edge->trackNodes();
    return QGraphicsItem::itemChange(change, value);
}

void GraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    label->setText(getGraphNode().getText());
    label->setPos(calcLabelPosition());
    QGraphicsEllipseItem::paint(painter, option, widget);
}

QPointF GraphicsNodeItem::calcLabelPosition()
{
    QString text = getGraphNode().getText();
    if (text.length() != 0)
    {
        QFontMetrics metrics(label->font());
        return QPointF(NODE_DIAMETER/2 - metrics.width(text)/2, -5 - metrics.height());
    }
    else
        return QPointF();
}
