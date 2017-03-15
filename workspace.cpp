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
    event->accept();
    createNode(event->pos());
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    if (nodeCreationMode)
        createNode(event->pos());
    else
//        if (edgeCreationMode)
//        {
//            Node* selectedNode = qgraphicsitem_cast<Node *>(scene()->itemAt(mapToScene(event->localPos())));
//            if (selectedNode)
//                selectedNode->setSelected(true);
//            if (scene()->selectedItems().count() < 2)
//            {

//                Node* firstNode =
//            }
//            if (getSelectedNodePair() != NodePair())
//                createEdge();
//        }
//        else
    QGraphicsView::mousePressEvent(event);
}

void Workspace::toggleNodeCreationMode(bool isToggled)
{
    nodeCreationMode = isToggled;
}

void Workspace::toggleEdgeCreationMode(bool isToggled)
{
    edgeCreationMode = isToggled;
}

void Workspace::createNode(const QPoint& pos)
{
    Node* newNode = new Node(mapToScene(pos));
    scene()->addItem(newNode);
}

void Workspace::createEdge()
{
    NodePair selectedNodes = getSelectedNodePair();
    if (selectedNodes != NodePair())
    {
        Edge* newEdge = new Edge(selectedNodes.first, selectedNodes.second);
        scene()->addItem(newEdge);
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
