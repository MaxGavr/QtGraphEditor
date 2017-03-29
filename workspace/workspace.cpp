#include "workspace.h"
#include "graphics/graphicsedgeitem.h"

Workspace::Workspace(MainWindow* parent)
    : QGraphicsView(parent)
{
    QGraphicsScene* newScene = new QGraphicsScene(0, 0, WIDTH, HEIGHT);
    setScene(newScene);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    graph = new Graph();
}

void Workspace::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (!nodeCreationMode && !edgeCreationMode)
        createNode(event->pos());
    else
        QGraphicsView::mouseDoubleClickEvent(event);
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    if (nodeCreationMode)
        createNode(event->pos());
    else
        if (edgeCreationMode)
        {
            GraphicsNodeItem* selectedNode = qgraphicsitem_cast<GraphicsNodeItem *>
                    (scene()->itemAt(mapToScene(event->pos()), QGraphicsView::transform()));
            if (selectedNode)
            {
                selectedNode->setSelected(true);
                if (!selectedNodes.first)
                {
                    selectedNodes.first = selectedNode;
                }
                else
                {
                    if (selectedNodes.first && !selectedNodes.second)
                    {
                        selectedNodes.second = selectedNode;
                        createEdge();
                    }
                }
            }
        }
        else
            QGraphicsView::mousePressEvent(event);
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

void Workspace::toggleNodeCreationMode(bool isToggled)
{
    nodeCreationMode = isToggled;
    if (isToggled)
        scene()->clearSelection();
}

void Workspace::toggleEdgeCreationMode(bool isToggled)
{
    edgeCreationMode = isToggled;
    if (isToggled)
        scene()->clearSelection();
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
