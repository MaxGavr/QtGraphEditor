#include "graphedge.h"
#include "graphnode.h"

using namespace GraphModel;


Edge::Edge(Node* start, Node* end, int weight, bool oriented)
{
    setStartNode(start);
    setEndNode(end);
    setWeight(weight);
    this->oriented = oriented;
}

Edge::~Edge()
{
    startNode->removeEdge(this);
    endNode->removeEdge(this);
}

Edge::Index Edge::getIndex() const
{
    return Index(startNode->getIndex(), endNode->getIndex());
}

bool Edge::isOriented() const
{
    return oriented;
}

bool Edge::isLoop() const
{
    return startNode == endNode;
}

void Edge::setStartNode(Node *node)
{
    startNode = node;
    node->addEdge(this);
}

void Edge::setEndNode(Node *node)
{
    endNode = node;
    node->addEdge(this);
}

int Edge::getWeight() const
{
    return weight;
}

void Edge::setWeight(int w)
{
    weight = w;
}

Node::const_ref Edge::getAdjacentNode(Node::const_ref node) const
{
    if (!isLoop())
    {
        if (node == *startNode)
            return *endNode;
        else if (node == *endNode && !isOriented())
            return *startNode;
    }
    throw bad_graph_node();
}

bool GraphModel::operator== (const Edge& firstEdge, const Edge& secondEdge)
{
    bool equalNodesStraight = (firstEdge.startNode == secondEdge.startNode) &&
                              (firstEdge.endNode == secondEdge.endNode);
    bool equalNodesMix = (firstEdge.endNode == secondEdge.startNode) &&
                         (firstEdge.startNode == secondEdge.endNode);
    bool equalWeight = (firstEdge.getWeight() == secondEdge.getWeight());
    return (equalNodesStraight || equalNodesMix) && equalWeight;
}

bool GraphModel::operator==(const Edge::Index &i, const Edge::Index &j)
{
    bool equalStraight = (i.first == j.first) && (i.second == j.second);
    bool equalReverse = (i.first == j.second) && (i.second == j.first);
    return (equalStraight || equalReverse);
}
