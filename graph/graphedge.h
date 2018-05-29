#pragma once

#include <QPair>

#include "graphnode.h"
#include "exceptions.h"


namespace GraphModel
{

class Edge
{
public:
    using const_ref = const Edge&;
    using Index = QPair<Node::Index, Node::Index>;

    Edge(Node* start, Node* end, int weight = 0, bool oriented = false);
    ~Edge();

    Edge::Index getIndex() const;
    bool isOriented() const;
    bool isLoop() const;

    int getWeight() const;
    void setWeight(int w);

    Node::const_ref getAdjacentNode(Node::const_ref node) const;

    friend bool operator== (const Edge& firstEdge, const Edge& secondEdge);

private:
    void setStartNode(Node* node);
    void setEndNode(Node* node);

    Node* startNode;
    Node* endNode;
    bool oriented;

    int weight;

    friend class Graph;
    friend class Node;
};

bool operator== (const Edge& firstEdge, const Edge& secondEdge);
bool operator== (const Edge::Index& first, const Edge::Index& second);

}
