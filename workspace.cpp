#include "workspace.h"
#include "edge.h"
#include "node.h"

Workspace::Workspace(MainWindow* parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene(0, 0, WIDTH, HEIGHT);
    view = new QGraphicsView(scene, this);
    view->setMaximumSize(WIDTH, HEIGHT);
    view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(view);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void Workspace::mouseDoubleClickEvent(QMouseEvent *event)
{
    createNode(event->pos());
}

void Workspace::createNode(const QPointF& pos)
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
        Node* firstNode = qgraphicsitem_cast<Node *>(selected.first());
        Node* secondNode = qgraphicsitem_cast<Node *>(selected.last());
        if (firstNode && secondNode)
            return NodePair(firstNode, secondNode);
    }
    return NodePair();
}
