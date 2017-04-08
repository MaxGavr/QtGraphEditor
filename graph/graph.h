#pragma once

#include <QVector>

#include "graphnode.h"

class Graph
{
public:
    Graph();

    GraphNode::const_reference addNode();
    GraphNode::const_reference addNode(QString idtf);
    void removeNode(GraphNode::const_reference node);
    void setNodeIdtf(GraphNode::const_reference node, QString idtf);

    GraphEdge* addEdge(GraphNode::const_reference firstNode, GraphNode::const_reference secondNode);
    void removeEdge(GraphEdge::const_reference edge);
    void setEdgeWeight(GraphEdge::const_reference edge, int weight);

private:
    GraphNode* findNodeByIndex(int index);
    GraphEdge* findEdgeByIndex(const GraphEdge::GraphEdgeIndex& index);

    QLinkedList<GraphNode *> nodes;
    QLinkedList<GraphEdge *> edges;

    int setNodeIndex();
    void removeNodeIndex(int i);

    QVector<int> nodeIndices;
};
