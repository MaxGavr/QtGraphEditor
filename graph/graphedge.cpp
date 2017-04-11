#include "graphedge.h"
#include "graphnode.h"

GraphEdge::GraphEdge(GraphNode* startNode, GraphNode* endNode, int weight)
{
    setStartNode(startNode);
    setEndNode(endNode);
    setWeight(weight);
}

GraphEdge::~GraphEdge()
{
    GraphEdgeIndex index = getEdgeIndex();
    QString msg = QString("Graph edge %1 - %2 deleted")
            .arg(QString::number(index.first))
            .arg(QString::number(index.second));
    qInfo("%s", msg.toLatin1().constData());
    getStartNode()->removeEdge(this);
    getEndNode()->removeEdge(this);
}

GraphEdge::GraphEdgeIndex GraphEdge::getEdgeIndex() const
{
    return GraphEdgeIndex(startNode->getIndex(), endNode->getIndex());
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

bool operator==(const GraphEdge::GraphEdgeIndex &i, const GraphEdge::GraphEdgeIndex &j)
{
    bool equalStraight = (i.first == j.first) && (i.second == j.second);
    bool equalReverse = (i.first == j.second) && (i.second == j.first);
    return (equalStraight || equalReverse);
}
