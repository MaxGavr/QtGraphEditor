#include "workspace.h"
#include "edge.h"
#include "node.h"

Workspace::Workspace(MainWindow* parent)
    : QGraphicsView(parent)
{
    QGraphicsScene* newScene = new QGraphicsScene(0, 0, WIDTH, HEIGHT);
    setScene(newScene);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
            Node* selectedNode = qgraphicsitem_cast<Node *>(scene()->itemAt(mapToScene(event->pos()), QGraphicsView::transform()));
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
                        createEdge(selectedNodes);
                    }
                }
            }
        }
        else
            QGraphicsView::mousePressEvent(event);
}

void Workspace::toggleNodeCreationMode(bool isToggled)
{
    nodeCreationMode = isToggled;
}

void Workspace::toggleEdgeCreationMode(bool isToggled)
{
    edgeCreationMode = isToggled;
    if (isToggled)
        scene()->clearSelection();
}

void Workspace::createNode(const QPoint& pos)
{
    Node* newNode = new Node(mapToScene(pos));
    scene()->addItem(newNode);
}

void Workspace::createEdge()
{
    selectedNodes = getSelectedNodePair();
    if (selectedNodes != NodePair())
    {
        Edge* newEdge = new Edge(selectedNodes.first, selectedNodes.second);
        scene()->addItem(newEdge);
        selectedNodes = NodePair();
        scene()->clearSelection();
    }
}

void Workspace::createEdge(const NodePair)
{
    if (selectedNodes.first && selectedNodes.second)
    {
        Edge* newEdge = new Edge(selectedNodes.first, selectedNodes.second);
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
        Node* firstNode = qgraphicsitem_cast<Node *>(selected.first());
        Node* secondNode = qgraphicsitem_cast<Node *>(selected.last());
        if (firstNode && secondNode)
            return NodePair(firstNode, secondNode);
    }
    return NodePair();
}
