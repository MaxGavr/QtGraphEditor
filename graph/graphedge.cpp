#include "graphedge.h"
#include "graphnode.h"

GraphEdge::GraphEdge(GraphNode *start, GraphNode *end)
{
    setStartNode(start);
    setEndNode(end);
}

GraphEdge::~GraphEdge()
{
    qInfo("edge deleted");
    getStartNode()->removeEdge(this);
    getEndNode()->removeEdge(this);
}

GraphEdge::GraphEdgeIndex GraphEdge::getEdgeIndex() const
{
    return GraphEdgeIndex(startNode->getIndex(), startNode->getIndex());
}

GraphNode* GraphEdge::getStartNode()
{
    return startNode;
}

GraphNode* GraphEdge::getEndNode()
{
    return endNode;
}

void GraphEdge::setStartNode(GraphNode *node)
{
    startNode = node;
}

void GraphEdge::setEndNode(GraphNode *node)
{
    endNode = node;
}

int GraphEdge::getWeight() const
{
    return weight;
}

void GraphEdge::setWeight(int w)
{
    weight = w;
}
