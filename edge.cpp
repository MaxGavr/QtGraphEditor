#include "edge.h"
#include "node.h"

Edge::Edge(Node* begin, Node* end)
{
    startNode = begin;
    endNode = end;

    startNode->addEdge(this);
    endNode->addEdge(this);

    setFlags(ItemIsSelectable);
    setPen(QPen(Qt::darkGray, 3));
    setZValue(-1);

    trackNodes();
}

Node* Edge::getStartNode()
{
    return startNode;
}

Node* Edge::getEndNode()
{
    return endNode;
}

void Edge::trackNodes()
{
    setLine(QLineF(startNode->getCenterPos(), endNode->getCenterPos()));
}
