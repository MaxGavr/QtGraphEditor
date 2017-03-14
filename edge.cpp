#include "edge.h"
#include "node.h"

Edge::Edge(Node* begin, Node* end)
{
    startNode = begin;
    endNode = end;

    startNode->addEdge(this);
    endNode->addEdge(this);

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
    setLine(QLineF(startNode->pos(), endNode->pos()));
}
