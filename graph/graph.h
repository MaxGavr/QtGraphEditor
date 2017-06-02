#pragma once

#include <QVector>
#include <QMap>
#include <set>
#include <queue>

#include "graphedge.h"
#include "exceptions.h"

class Graph
{
public:
    using AdjacencyList = QMap< int, QList< QPair<int, int> > > ;

    Graph();
    ~Graph();

    GraphNode::const_ref addNode(QString idtf = "");
    GraphNode::const_ref addNode(int index, QString idtf = "");
    GraphNode::const_ref addNode(GraphNode::const_ref node);
    void removeNode(GraphNode::const_ref node);
    void setNodeIdtf(GraphNode::const_ref node, QString idtf);

    GraphEdge::const_ref addEdge(GraphNode::const_ref firstNode,
                                       GraphNode::const_ref secondNode,
                                       int weight = 0, bool oriented = false);
    GraphEdge::const_ref addEdge(int firstIndex, int secondIndex, int weight = 0, bool oriented = false);
    void removeEdge(GraphEdge::const_ref edge);
    void setEdgeWeight(GraphEdge::const_ref edge, int weight);

    bool containsNode(GraphNode::const_ref node) const;
    bool containsEdge(GraphNode::const_ref firstNode,
                      GraphNode::const_ref secondNode) const;

    GraphNode::const_ref retrieveNode(int index) const;
    GraphEdge::const_ref retrieveEdge(GraphEdge::EdgeIndex index) const;

    bool isEmpty() const;

    int countNodes() const;
    int countEdges() const;

    AdjacencyList getAdjacencyList() const;

private:
    GraphNode* findNodeByIndex(int index);
    GraphEdge* findEdgeByIndex(const GraphEdge::EdgeIndex& index);

    QLinkedList<GraphNode *> nodes;
    QLinkedList<GraphEdge *> edges;

    int setNodeIndex();
    void removeNodeIndex(int i);
    bool validateNodeIndex(int i) const;
    bool validateEdgeIndex(GraphEdge::EdgeIndex i);

    std::set<int> nodeIndices;
};
