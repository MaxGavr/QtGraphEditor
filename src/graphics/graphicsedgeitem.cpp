#include "graphicsedgeitem.h"

using namespace GraphModel;


const int GraphicsEdgeItem::ARROW_SIZE = 15;
const QSizeF GraphicsEdgeItem::loopSize = QSizeF(50, 50);

GraphicsEdgeItem::GraphicsEdgeItem(GraphicsNodeItem* begin, GraphicsNodeItem* end, const Edge &edge)
    : graphEdge(edge)
{
    startNodeItem = begin;
    endNodeItem = end;

    startNodeItem->addEdgeItem(this);
    endNodeItem->addEdgeItem(this);

    setFlags(ItemIsSelectable);
    setPen(QPen(Qt::darkGray, 3));
    defaultPen = pen();
    setZValue(-1);

    label = new QGraphicsSimpleTextItem(QString::number(getGraphEdge().getWeight()), this);
    label->setFont(QFont("Helvetica", 12));

    if (isLoop())
    {
        QRectF loopRect = QRectF(QPointF(0, 0), loopSize);
        loop = new QGraphicsEllipseItem(loopRect, startNodeItem);
        loop->setFlags(ItemStacksBehindParent);
        loop->setPen(getDefaultPen());
    }

    trackNodes();
}

GraphicsEdgeItem::~GraphicsEdgeItem()
{
    getStartNodeItem()->removeEdgeItem(this);
    getEndNodeItem()->removeEdgeItem(this);
    delete label;
    if (isLoop())
        delete loop;
}

const Edge& GraphicsEdgeItem::getGraphEdge() const
{
    return graphEdge;
}

bool GraphicsEdgeItem::isOriented() const
{
    return graphEdge.isOriented();
}

bool GraphicsEdgeItem::isLoop() const
{
    return graphEdge.isLoop();
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
    if (isLoop())
        loop->setPos(calcLoopPosition());
}

void GraphicsEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (getStartNodeItem()->collidesWithItem(getEndNodeItem()))
        QGraphicsLineItem::paint(painter, option, widget);

    if (!isLoop())
    {
        label->setText(QString::number(getGraphEdge().getWeight()));
        if (getGraphEdge().getWeight() == 0)
            label->hide();
        else
            label->show();
        label->setPos(calcLabelPosition());
    }
    else
        label->hide();

    if (isOriented())
    {
        painter->setPen(pen());
        painter->setBrush(Qt::darkGray);

        GraphicsNodeItem* startNode = getStartNodeItem();
        QLineF fullLine = QLineF(startNodeItem->getCenterPos(), endNodeItem->getCenterPos());

        int nodeRadius = GraphicsNodeItem::NODE_DIAMETER / 2;
        QPointF intersectionPoint = fullLine.pointAt(1 - ((nodeRadius + 5) / fullLine.length()));

        setLine(QLineF(intersectionPoint, startNode->getCenterPos()));

        const qreal Pi = 3.14;

        double angle = ::acos(line().dx() / line().length());
        if (line().dy() >= 0)
            angle = (Pi * 2) - angle;

        QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * ARROW_SIZE,
                                        cos(angle + Pi / 3) * ARROW_SIZE);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * ARROW_SIZE,
                                        cos(angle + Pi - Pi / 3) * ARROW_SIZE);

        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;

        painter->drawLine(line());
        painter->drawPolygon(arrowHead);
    }

    QGraphicsLineItem::paint(painter, option, widget);
}

QRectF GraphicsEdgeItem::boundingRect() const
{
    if (isOriented())
    {
        qreal extra = (pen().width() + ARROW_SIZE) / 2.0;
        QSize edgeSize = QSize(line().p2().x() - line().p1().x(),
                               line().p2().y() - line().p1().y());
        return QRectF(line().p1(), edgeSize).normalized().adjusted(-extra, -extra, extra, extra);
    }
    else
    {
        if (isLoop())
        {
            QRectF rect = loop->boundingRect();
            return QRectF(mapFromItem(loop, rect.topLeft()), loopSize);
        }
    }
    return QGraphicsLineItem::boundingRect();
}

QPainterPath GraphicsEdgeItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    if (isOriented())
        path.addPolygon(arrowHead);
    else
        if (isLoop())
            path = mapFromItem(loop, loop->shape());
    return path;
}

QPen GraphicsEdgeItem::getDefaultPen()
{
    return defaultPen;
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

QPointF GraphicsEdgeItem::calcLoopPosition() const
{
    QPointF nodeCenter = startNodeItem->mapFromScene(startNodeItem->getCenterPos());
    return QPointF(nodeCenter.x() - loopSize.width() / 2, nodeCenter.y() - loopSize.height());
}
