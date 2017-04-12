#include "graphnode.h"

GraphNode::GraphNode(int i)
{
    setIndex(i);
    setText(QString::number(getIndex()));
    QString msg = QString("Graph node %1 created").arg(QString::number(getIndex()));
    qInfo("%s", msg.toLatin1().constData());
}

GraphNode::GraphNode(int i, const QString& str)
{
    setIndex(i);
    setText(str);
    QString msg = QString("Graph node %1 created").arg(QString::number(getIndex()));
    qInfo("%s", msg.toLatin1().constData());
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

QList< QPair<int, int> > GraphNode::getAdjacentNodes() const
{
    QList< QPair<int,int> > adjacentNodes;
    foreach (GraphEdge* edge, edges)
    {
        GraphEdge::GraphEdgeIndex edgeIndex = edge->getEdgeIndex();
        QPair<int, int> adjacent;
        if (getIndex() == edgeIndex.first)
            adjacent.second = edgeIndex.second;
        else
            adjacent.second = edgeIndex.first;
        adjacent.first = edge->getWeight();
        adjacentNodes.append(adjacent);
    }
    return adjacentNodes;
}

void GraphNode::setIndex(int i)
{
    index = i;
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
