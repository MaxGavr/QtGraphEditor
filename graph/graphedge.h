#pragma once

#include <QLinkedList>
#include <QPair>

#include <iostream>

class GraphNode;

class GraphEdge
{
    friend class Graph;
    friend class GraphNode;

public:
    typedef const GraphEdge& const_reference;
    typedef QPair<int, int> GraphEdgeIndex;

    GraphEdge(GraphNode* start, GraphNode* end, int weight = 0);
    ~GraphEdge();

    GraphEdgeIndex getEdgeIndex() const;

    int getWeight() const;
    void setWeight(int w);

private:
    void setStartNode(GraphNode* node);
    void setEndNode(GraphNode* node);

    GraphNode* startNode;
    GraphNode* endNode;

    int weight;
};

bool operator== (const GraphEdge::GraphEdgeIndex& first, const GraphEdge::GraphEdgeIndex& second);
