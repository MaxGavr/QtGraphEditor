#pragma once

#include <QList>

#include "graphnode.h"
#include "graphedge.h"

class Graph;


class IncidenceMatrix
{
public:
    IncidenceMatrix(const Graph& graph);

    int getAt(int column, int row) const;

    int getRowsCount() const;
    int getColumnsCount() const;

    QString getNodeIdentifier(int row) const;
    QString getEdgeIdentifier(int column) const;

private:
    int nodesCount;

    QMap<GraphNode::Index, QString> nodeIdentifiers;
    QList<GraphEdge::Index> edgeIndices;
};
