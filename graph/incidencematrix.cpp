#include <functional>
#include <algorithm>

#include "graph.h"
#include "incidencematrix.h"

using namespace GraphModel;


IncidenceMatrix::IncidenceMatrix(const Graph& graph)
{
    nodesCount = graph.countNodes();

    // get nodes identifiers
    for (Node::Index i = 0; i < nodesCount; ++i)
        nodeIdentifiers.insert(i, graph.retrieveNode(i).getText());

    edgeIndices = graph.getEdges();

    // sort edge indices in ascending order by the sum of indices of incident nodes
    auto lessIndexSum = [] (Edge::Index firstIndex, Edge::Index secondIndex) -> bool {
        return (firstIndex.first + firstIndex.second) < (secondIndex.first + secondIndex.second);
    };
    std::sort(edgeIndices.begin(), edgeIndices.end(), lessIndexSum);

    // store orientation of each edge
    foreach (Edge::Index edgeIndex, edgeIndices)
        edgeOrientation.insert(edgeIndex, graph.retrieveEdge(edgeIndex).isOriented());
}

int IncidenceMatrix::getAt(int column, int row) const
{
    if (column < 0 || column >= getColumnsCount() || row < 0 || row >= getRowsCount())
        throw std::out_of_range("Invalid arguments!");

    Node::Index nodeIndex = (Node::Index)row;
    Edge::Index edgeIndex = edgeIndices.at(column);

    // oriented edge
    if (edgeOrientation[edgeIndex])
    {
        if (nodeIndex == edgeIndex.first)
            return -1;
        else if (nodeIndex == edgeIndex.second)
            return 1;
        else
            return 0;
    }
    // not oriented edge
    else
    {
        if (nodeIndex == edgeIndex.first || nodeIndex == edgeIndex.second)
            return 1;
        else
            return 0;
    }
}

int IncidenceMatrix::getRowsCount() const
{
    return nodesCount;
}

int IncidenceMatrix::getColumnsCount() const
{
    return edgeIndices.length();
}

QString IncidenceMatrix::getNodeIdentifier(int row) const
{
    if (row < 0 || row >= getRowsCount())
        throw std::out_of_range("Invalid argument!");

    return *nodeIdentifiers.find((Node::Index)row);
}

QString IncidenceMatrix::getEdgeIdentifier(int column) const
{
    if (column < 0 || column >= getColumnsCount())
        throw std::out_of_range("Invalid argument!");

    Edge::Index edgeIndex = edgeIndices.at(column);

    return QString::number(edgeIndex.first) + "-" + QString::number(edgeIndex.second);
}
