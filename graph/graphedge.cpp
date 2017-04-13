#include "graphedge.h"
#include "graphnode.h"

GraphEdge::GraphEdge(GraphNode* start, GraphNode* end, int weight)
{
    setStartNode(start);
    setEndNode(end);
    setWeight(weight);
}

GraphEdge::~GraphEdge()
{
    startNode->removeEdge(this);
    endNode->removeEdge(this);
}

GraphEdge::EdgeIndex GraphEdge::getEdgeIndex() const
{
    return EdgeIndex(startNode->getIndex(), endNode->getIndex());
}

void GraphEdge::setStartNode(GraphNode *node)
{
    startNode = node;
    node->addEdge(this);
}

void GraphEdge::setEndNode(GraphNode *node)
{
    endNode = node;
    node->addEdge(this);
}

int GraphEdge::getWeight() const
{
    return weight;
}

void GraphEdge::setWeight(int w)
{
    weight = w;
}

bool operator== (GraphEdge::const_ref firstEdge, GraphEdge::const_ref secondEdge)
{
    bool equalNodesStraight = (firstEdge.startNode == secondEdge.startNode) &&
                              (firstEdge.endNode == secondEdge.endNode);
    bool equalNodesMix = (firstEdge.endNode == secondEdge.startNode) &&
                         (firstEdge.startNode == secondEdge.endNode);
    bool equalWeight = firstEdge.getWeight() == secondEdge.getWeight();
    return (equalNodesStraight || equalNodesMix) && equalWeight;
}

bool operator==(const GraphEdge::EdgeIndex &i, const GraphEdge::EdgeIndex &j)
{
    bool equalStraight = (i.first == j.first) && (i.second == j.second);
    bool equalReverse = (i.first == j.second) && (i.second == j.first);
    return (equalStraight || equalReverse);
}
