#pragma once

#include <QVector>
#include <QMap>
#include <set>

#include "graphedge.h"
#include "exceptions.h"


class Graph
{
public:
    using AdjacencyList = QMap<GraphNode::Index, GraphNode::AdjacentNodes>;

    Graph();
    ~Graph();

    GraphNode::const_ref addNode(QString idtf = "");
    GraphNode::const_ref addNode(GraphNode::Index index, QString idtf = "");
    GraphNode::const_ref addNode(GraphNode::const_ref node);

    GraphEdge::const_ref addEdge(GraphNode::const_ref firstNode,
                                 GraphNode::const_ref secondNode,
                                 int weight = 0, bool oriented = false);
    GraphEdge::const_ref addEdge(GraphNode::Index firstIndex, GraphNode::Index secondIndex, int weight = 0, bool oriented = false);

    void removeEdge(GraphEdge::const_ref edge);
    void removeNode(GraphNode::const_ref node);

    void setNodeIdtf(GraphNode::const_ref node, QString idtf);
    void setEdgeWeight(GraphEdge::const_ref edge, int weight);

    bool containsNode(GraphNode::const_ref node) const;
    bool containsEdge(GraphNode::const_ref firstNode,
                      GraphNode::const_ref secondNode) const;

    GraphNode::const_ref retrieveNode(GraphNode::Index index) const;
    GraphEdge::const_ref retrieveEdge(GraphEdge::Index index) const;

    bool isEmpty() const;

    int countNodes() const;
    int countEdges() const;

    QList<GraphEdge::Index> getEdges() const;

    AdjacencyList getAdjacencyList() const;

private:
    GraphNode* findNodeByIndex(GraphNode::Index index);
    GraphEdge* findEdgeByIndex(const GraphEdge::Index& index);

    QLinkedList<GraphNode *> nodes;
    QLinkedList<GraphEdge *> edges;

    int setNodeIndex();
    void removeNodeIndex(GraphNode::Index i);
    bool validateNodeIndex(GraphNode::Index i) const;
    bool validateEdgeIndex(GraphEdge::Index i);

    std::set<GraphNode::Index> nodeIndices;
};
