#pragma once

#include <QList>

#include "graphnode.h"
#include "graphedge.h"


namespace GraphModel
{

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

    QMap<Node::Index, QString> nodeIdentifiers;
    QList<Edge::Index> edgeIndices;
};

}
