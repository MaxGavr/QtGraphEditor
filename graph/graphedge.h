#pragma once

#include <QPair>

#include "graphnode.h"
#include "exceptions.h"


class GraphEdge
{
public:
    using const_ref = const GraphEdge&;
    using Index = QPair<GraphNode::Index, GraphNode::Index>;

    GraphEdge(GraphNode* start, GraphNode* end, int weight = 0, bool oriented = false);
    ~GraphEdge();

    GraphEdge::Index getIndex() const;
    bool isOriented() const;
    bool isLoop() const;

    int getWeight() const;
    void setWeight(int w);

    GraphNode::const_ref getAdjacentNode(GraphNode::const_ref node) const;

    friend bool operator== (GraphEdge::const_ref firstEdge, GraphEdge::const_ref secondEdge);

private:
    void setStartNode(GraphNode* node);
    void setEndNode(GraphNode* node);

    GraphNode* startNode;
    GraphNode* endNode;
    bool oriented;

    int weight;

    friend class Graph;
    friend class GraphNode;
};

bool operator== (GraphEdge::const_ref firstEdge, GraphEdge::const_ref secondEdge);
bool operator== (const GraphEdge::Index& first, const GraphEdge::Index& second);
