#include "workspace.h"
#include "edge.h"
#include "node.h"

Workspace::Workspace(MainWindow* parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene(0, 0, 640, 480);
    view = new QGraphicsView(scene, this);
    view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);
}

void Workspace::mouseDoubleClickEvent(QMouseEvent *event)
{
    createNode(event->pos());
}

void Workspace::createNode(QPoint pos)
{
    Node* newNode = new Node(pos);
    scene->addItem(newNode);
}

void Workspace::createEdge()
{
    NodePair selectedNodes = getSelectedNodePair();
    if (selectedNodes != NodePair())
    {
        Edge* newEdge = new Edge(selectedNodes.first, selectedNodes.second);
        scene->addItem(newEdge);
    }
}

Workspace::NodePair Workspace::getSelectedNodePair()
{
    QList<QGraphicsItem *> selected = scene->selectedItems();
    if (selected.count() == 2)
    {
        Node* firstNode = dynamic_cast<Node *>(selected.first());
        Node* secondNode = dynamic_cast<Node *>(selected.last());
        if (firstNode && secondNode)
            return NodePair(firstNode, secondNode);
    }
    return NodePair();
}
