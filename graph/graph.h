#pragma once

#include <QVector>
#include <QMap>
#include <set>
#include <queue>

#include "graphnode.h"
#include "exceptions.h"

class Graph
{
public:
    typedef QMap< int, QList< QPair<int, int> > > AdjacencyList;

    Graph();
    ~Graph();

    GraphNode::const_reference addNode(QString idtf = "");
    GraphNode::const_reference addNode(int index, QString idtf = "");
    GraphNode::const_reference addNode(GraphNode::const_reference node);
    void removeNode(GraphNode::const_reference node);
    void setNodeIdtf(GraphNode::const_reference node, QString idtf);

    GraphEdge::const_reference addEdge(GraphNode::const_reference firstNode,
                                       GraphNode::const_reference secondNode,
                                       int weight = 0);
    GraphEdge::const_reference addEdge(int firstIndex, int secondIndex, int weight = 0);
    void removeEdge(GraphEdge::const_reference edge);
    void setEdgeWeight(GraphEdge::const_reference edge, int weight);

    bool containsNode(GraphNode::const_reference node) const;
    bool containsEdge(GraphNode::const_reference firstNode,
                      GraphNode::const_reference secondNode) const;

    GraphNode::const_reference retrieveNode(int index) const;
    GraphEdge::const_reference retrieveEdge(GraphEdge::GraphEdgeIndex index) const;

    int countNodes() const;
    int countEdges() const;

    AdjacencyList getAdjacencyList() const;

private:
    GraphNode* findNodeByIndex(int index);
    GraphEdge* findEdgeByIndex(const GraphEdge::GraphEdgeIndex& index);

    QLinkedList<GraphNode *> nodes;
    QLinkedList<GraphEdge *> edges;

    int setNodeIndex();
    void removeNodeIndex(int i);
    bool validateNodeIndex(int i) const;
    bool validateEdgeIndex(GraphEdge::GraphEdgeIndex i);

    std::set<int> nodeIndices;
};
