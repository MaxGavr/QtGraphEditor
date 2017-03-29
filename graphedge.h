#pragma once

#include <QLinkedList>
#include <QPair>

#include <iostream>

class GraphNode;

class GraphEdge
{
public:
    typedef const GraphEdge& const_reference;
    typedef QPair<int, int> GraphEdgeIndex;

    GraphEdge(GraphNode* start, GraphNode* end);
    ~GraphEdge();

    GraphEdgeIndex getEdgeIndex() const;

    GraphNode* getStartNode();
    GraphNode* getEndNode();

    void setStartNode(GraphNode* node);
    void setEndNode(GraphNode* node);

    int getWeight() const;
    void setWeight(int w);

private:
    GraphNode* startNode;
    GraphNode* endNode;

    int weight;
};
