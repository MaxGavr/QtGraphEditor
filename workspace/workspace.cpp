#include "workspace.h"
#include "graphics/graphicsedgeitem.h"

Workspace::Workspace(MainWindow* parent)
    : QGraphicsView(parent)
{
    QGraphicsScene* newScene = new QGraphicsScene(0, 0, WIDTH, HEIGHT);
    setScene(newScene);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setMaximumSize(QSize(WIDTH, HEIGHT));
    setMouseTracking(true);

    graph = new Graph();
    drawingLine = NULL;
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    if (drawingLine && (toggledMode == edgeCreationMode))
        drawingLine->setLine(QLineF(selectedNodes.first->getCenterPos(), mapToScene(event->pos())));
    else
        QGraphicsView::mouseMoveEvent(event);
}

void Workspace::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (toggledMode == defaultMode)
        createNode(event->pos());
    else
        QGraphicsView::mouseDoubleClickEvent(event);
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    switch (toggledMode)
    {
    case defaultMode:
    {
        QGraphicsView::mousePressEvent(event);
        break;
    }
    case nodeCreationMode:
    {
        createNode(event->pos());
        break;
    }
    case edgeCreationMode:
    {
        manageEdgeCreation(event->pos());
        break;
    }
    case deletionMode:
    {
        deleteElementAtPosition(event->pos());
        break;
    }
    }
}

void Workspace::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Delete:
        {
            QList<QGraphicsItem *> items = scene()->selectedItems();

            foreach (QGraphicsItem* item, items)
                if (GraphicsEdgeItem* edge = qgraphicsitem_cast<GraphicsEdgeItem *>(item))
                {
                    items.removeOne(edge);
                    deleteEdge(edge);
                }
            foreach (QGraphicsItem* item, items)
            {
                items.removeOne(item);
                deleteNode(qgraphicsitem_cast<GraphicsNodeItem *>(item));
            }

            break;
        }
    }
}

void Workspace::createNode(const QPoint& pos)
{
    GraphNode::const_reference newGraphNode = graph->addNode();
    GraphicsNodeItem* newNodeItem = new GraphicsNodeItem(mapToScene(pos), newGraphNode);
    scene()->addItem(newNodeItem);
}

void Workspace::deleteElementAtPosition(QPoint pos)
{
    QGraphicsItem* item = scene()->itemAt(QPointF(mapToScene(pos)), QTransform());
    if (GraphicsNodeItem* node = qgraphicsitem_cast<GraphicsNodeItem*>(item))
        deleteNode(node);
    else
        if (GraphicsEdgeItem* edge = qgraphicsitem_cast<GraphicsEdgeItem*>(item))
            deleteEdge(edge);
}

void Workspace::deleteNode(GraphicsNodeItem* nodeItem)
{
    foreach (GraphicsEdgeItem* edge, nodeItem->getEdgeItems())
        deleteEdge(edge);
    GraphNode::const_reference node = nodeItem->getGraphNode();
    delete nodeItem;
    graph->removeNode(node);
}

void Workspace::deleteEdge(GraphicsEdgeItem *edgeItem)
{
    GraphEdge::const_reference edge = edgeItem->getGraphEdge();
    delete edgeItem;
    graph->removeEdge(edge);
}

void Workspace::manageEdgeCreation(QPoint location)
{
    GraphicsNodeItem* topmostNode = getTopmostNodeItem(scene()->items(QPointF(mapToScene(location))));
    if (topmostNode)
    {
        topmostNode->setSelected(true);
        if (!selectedNodes.first)
        {
            selectedNodes.first = topmostNode;
            drawingLine = scene()->addLine(QLine(location, location));
        }
        else
            if (selectedNodes.first && !selectedNodes.second)
            {
                selectedNodes.second = topmostNode;
                delete drawingLine;
                drawingLine = NULL;
                createEdge();
            }
    }
}

void Workspace::createEdge()
{
    if (selectedNodes.first && selectedNodes.second)
    {
        GraphEdge* newGraphEdge = graph->addEdge(selectedNodes.first->getGraphNode(),
                                                 selectedNodes.second->getGraphNode());
        GraphicsEdgeItem* newEdge = new GraphicsEdgeItem(selectedNodes.first,
                                                         selectedNodes.second,
                                                         *newGraphEdge);
        scene()->addItem(newEdge);
        clearSelection();
    }
}

void Workspace::toggleMode(int mode, bool toggled)
{
    if (toggled)
    {
        toggledMode = mode;
        scene()->clearSelection();
    }
    else
        toggledMode = defaultMode;
}

void Workspace::toggleNodeCreationMode(bool isToggled)
{
    toggleMode(nodeCreationMode, isToggled);
}

void Workspace::toggleEdgeCreationMode(bool isToggled)
{
    toggleMode(edgeCreationMode, isToggled);
}

void Workspace::toggleDeletionMode(bool isToggled)
{
    toggleMode(deletionMode, isToggled);
}

void Workspace::deselectNodeItem(GraphicsNodeItem *nodeItem)
{
    nodeItem->setSelected(false);
    if (selectedNodes.first == nodeItem)
        selectedNodes.first = NULL;
    if (selectedNodes.second == nodeItem)
        selectedNodes.second = NULL;
}

GraphicsNodeItem *Workspace::getTopmostNodeItem(QList<QGraphicsItem *> items)
{
    if (!items.empty())
    {
        auto isEdge = [](QGraphicsItem* item) -> bool
                        { return qgraphicsitem_cast<GraphicsEdgeItem*>(item); };
        items.erase(std::remove_if(items.begin(), items.end(), isEdge), items.end());
        auto sortByZ = [](QGraphicsItem* firstItem, QGraphicsItem* secondItem)
                        { return firstItem->zValue() < secondItem->zValue(); };
        std::sort(items.begin(), items.end(), sortByZ);

        return qgraphicsitem_cast<GraphicsNodeItem*>(items.last());
    }
    else
        return NULL;

}

Workspace::NodePair Workspace::getSelectedNodePair()
{
    QList<QGraphicsItem *> selected = scene()->selectedItems();
    if (selected.count() == 2)
    {
        GraphicsNodeItem* firstNode = qgraphicsitem_cast<GraphicsNodeItem *>(selected.first());
        GraphicsNodeItem* secondNode = qgraphicsitem_cast<GraphicsNodeItem *>(selected.last());
        if (firstNode && secondNode)
            return NodePair(firstNode, secondNode);
    }
    return NodePair();
}

void Workspace::clearSelection()
{
    scene()->clearSelection();
    selectedNodes = NodePair();
}
