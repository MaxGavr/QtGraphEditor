#pragma once

#include <QVector>

#include "graphnode.h"

class Graph
{
public:
    Graph();

    GraphNode::const_reference addNode();
    GraphNode::const_reference addNode(QString nodeText);

    void removeNode(const GraphNode& node);

    GraphEdge* addEdge(const GraphNode& firstNode, const GraphNode& secondNode);
    void removeEdge(const GraphEdge& edge);

private:
    GraphNode* findNodeByIndex(int index);
    GraphEdge* findEdgeByIndex(const GraphEdge::GraphEdgeIndex& index);

    QLinkedList<GraphNode *> nodes;
    QLinkedList<GraphEdge *> edges;

    int setNodeIndex();
    void removeNodeIndex(int i);

    QVector<int> nodeIndices;
};
