#pragma once

#include <QLinkedList>
#include <QPair>

#include <iostream>

class GraphNode;

class GraphEdge
{
public:
    using const_ref = const GraphEdge&;
    using EdgeIndex = QPair<int, int>;

    friend class Graph;
    friend class GraphNode;
    friend bool operator== (GraphEdge::const_ref firstEdge, GraphEdge::const_ref secondEdge);

    GraphEdge(GraphNode* start, GraphNode* end, int weight = 0);
    ~GraphEdge();

    EdgeIndex getEdgeIndex() const;

    int getWeight() const;
    void setWeight(int w);

private:
    void setStartNode(GraphNode* node);
    void setEndNode(GraphNode* node);

    GraphNode* startNode;
    GraphNode* endNode;

    int weight;
};

bool operator== (GraphEdge::const_ref firstEdge, GraphEdge::const_ref secondEdge);
bool operator== (const GraphEdge::EdgeIndex& first, const GraphEdge::EdgeIndex& second);
