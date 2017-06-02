#pragma once

#include <QLinkedList>
#include <QPair>

#include <iostream>
#include "graphnode.h"
#include "exceptions.h"

class GraphEdge
{
public:
    using const_ref = const GraphEdge&;
    using EdgeIndex = QPair<int, int>;

    friend class Graph;
    friend class GraphNode;
    friend bool operator== (GraphEdge::const_ref firstEdge, GraphEdge::const_ref secondEdge);

    GraphEdge(GraphNode* start, GraphNode* end, int weight = 0, bool oriented = false);
    ~GraphEdge();

    EdgeIndex getEdgeIndex() const;
    bool isOriented() const;

    int getWeight() const;
    void setWeight(int w);

    GraphNode::const_ref getAdjacentNode(GraphNode::const_ref node) const;

private:
    void setStartNode(GraphNode* node);
    void setEndNode(GraphNode* node);

    GraphNode* startNode;
    GraphNode* endNode;
    bool oriented;

    int weight;
};

bool operator== (GraphEdge::const_ref firstEdge, GraphEdge::const_ref secondEdge);
bool operator== (const GraphEdge::EdgeIndex& first, const GraphEdge::EdgeIndex& second);
