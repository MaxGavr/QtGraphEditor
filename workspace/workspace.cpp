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

    graph = new Graph();
    drawingLine = NULL;
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

void Workspace::deleteNode(GraphicsNodeItem* nodeItem)
{
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
    GraphicsNodeItem* selectedNode = qgraphicsitem_cast<GraphicsNodeItem *>
            (scene()->itemAt(mapToScene(location), QGraphicsView::transform()));
    if (selectedNode)
    {
        selectedNode->setSelected(true);
        if (!selectedNodes.first)
            selectedNodes.first = selectedNode;
        else
            if (selectedNodes.first && !selectedNodes.second)
            {
                selectedNodes.second = selectedNode;
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
        selectedNodes = NodePair();
        scene()->clearSelection();
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
