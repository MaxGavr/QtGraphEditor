#include <QtAlgorithms>
#include <QList>

#include "graphnode.h"
#include "graphedge.h"


GraphNode::GraphNode(Index i)
{
    setIndex(i);
    setText(QString::number(getIndex()));
}

GraphNode::GraphNode(Index i, const QString& str)
{
    setIndex(i);
    setText(str);
}

GraphNode::~GraphNode()
{
    qDeleteAll(edges);
}

GraphNode::Index GraphNode::getIndex() const
{
    return index;
}

void GraphNode::addEdge(GraphEdge *edge)
{
    if (edge && !edges.contains(edge))
        edges.append(edge);
}

void GraphNode::removeEdge(GraphEdge *edge)
{
    if (edge)
        edges.removeOne(edge);
}

GraphNode::AdjacentNodes GraphNode::getAdjacentNodes() const
{
    AdjacentNodes adjacentNodes;
    foreach (GraphEdge* edge, edges)
    {
        try
        {
            QPair<int, GraphNode::Index> adjacent;
            adjacent.first = edge->getWeight();
            adjacent.second = edge->getAdjacentNode(*this).getIndex();
            adjacentNodes.append(adjacent);
        }
        catch (const bad_graph_node& e)
        {
            continue;
        }
    }
    return adjacentNodes;
}

void GraphNode::setIndex(Index i)
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

bool operator==(GraphNode::const_ref first, GraphNode::const_ref second)
{
    bool equalEdges = std::is_permutation(first.edges.begin(), first.edges.end(), second.edges.begin());
    bool equalIndices = (first.getIndex() == second.getIndex());
    bool equalText = (first.getText() == second.getText());
    return (equalEdges && equalIndices && equalText);
}

bool operator!=(GraphNode::const_ref first, GraphNode::const_ref second)
{
    return !(first == second);
}
