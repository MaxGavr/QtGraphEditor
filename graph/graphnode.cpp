#include <QtAlgorithms>
#include <QList>

#include "graphnode.h"
#include "graphedge.h"

using namespace GraphModel;


Node::Node(Index i)
{
    setIndex(i);
    setText(QString::number(getIndex()));
}

Node::Node(Index i, const QString& str)
{
    setIndex(i);
    setText(str);
}

Node::~Node()
{
    qDeleteAll(edges);
}

Node::Index Node::getIndex() const
{
    return index;
}

void Node::addEdge(Edge *edge)
{
    if (edge && !edges.contains(edge))
        edges.append(edge);
}

void Node::removeEdge(Edge *edge)
{
    if (edge)
        edges.removeOne(edge);
}

Node::AdjacentNodes Node::getAdjacentNodes() const
{
    AdjacentNodes adjacentNodes;
    foreach (Edge* edge, edges)
    {
        try
        {
            QPair<int, Node::Index> adjacent;
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

int Node::getDegree() const
{
    int degree = 0;

    foreach (Edge* edge, edges)
    {
        if (edge->isLoop())
            degree += 2;
        else
            degree += 1;
    }

    return degree;
}

int Node::getInputDegree() const
{
    int inputDegree = 0;

    foreach (Edge* edge, edges)
        if (edge->isOriented() && index == edge->getIndex().second)
            ++inputDegree;

    return inputDegree;
}

int Node::getOutputDegree() const
{
    int outputDegree = 0;

    foreach (Edge* edge, edges)
        if (edge->isOriented() && index == edge->getIndex().first)
            ++outputDegree;

    return outputDegree;
}

void Node::setIndex(Index i)
{
    index = i;
}

void Node::setText(const QString &str)
{
    text = str;
}

QString Node::getText() const
{
    return text;
}

bool GraphModel::operator==(Node::const_ref first, Node::const_ref second)
{
    bool equalEdges = std::is_permutation(first.edges.begin(), first.edges.end(), second.edges.begin());
    bool equalIndices = (first.getIndex() == second.getIndex());
    bool equalText = (first.getText() == second.getText());
    return (equalEdges && equalIndices && equalText);
}

bool GraphModel::operator!=(Node::const_ref first, Node::const_ref second)
{
    return !(first == second);
}
