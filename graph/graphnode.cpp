#include "graphnode.h"

GraphNode::GraphNode(int i)
    : index(i)
{
    setText(QString::number(getIndex()));
}

GraphNode::GraphNode(int i, const QString& str)
    : index(i)
{
    setText(str);
}

GraphNode::~GraphNode()
{
    QString msg = QString("Graph node %1 deleted").arg(QString::number(getIndex()));
    qInfo("%s", msg.toLatin1().constData());
    qDeleteAll(edges);
}

int GraphNode::getIndex() const
{
    return index;
}

void GraphNode::addEdge(GraphEdge *edge)
{
    if (edge && !edges.contains(edge))
    {
        edges.append(edge);
    }
}

void GraphNode::removeEdge(GraphEdge *edge)
{
    if (edge)
        edges.removeOne(edge);
}

QList<int> GraphNode::getAdjacentNodes() const
{
    QList<int> adjacentNodes;
    foreach (GraphEdge* edge, edges)
    {
        GraphEdge::GraphEdgeIndex edgeIndex = edge->getEdgeIndex();
        int adjacent;
        if (getIndex() == edgeIndex.first)
            adjacent = edgeIndex.second;
        else
            adjacent = edgeIndex.first;
        adjacentNodes.append(adjacent);
    }
    return adjacentNodes;
}

void GraphNode::setText(const QString &str)
{
    text = str;
}

QString GraphNode::getText() const
{
    return text;
}

bool operator==(GraphNode::const_reference first, GraphNode::const_reference second)
{
    bool equalEdges = std::is_permutation(first.edges.begin(), first.edges.end(), second.edges.begin());
    bool equalIndices = (first.getIndex() == second.getIndex());
    bool equalText = (first.getText() == second.getText());
    return (equalEdges && equalIndices && equalText);
}

bool operator!=(GraphNode::const_reference first, GraphNode::const_reference second)
{
    return !(first == second);
}
