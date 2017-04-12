#pragma once

#include "graph/graph.h"

class GraphAlgorithm
{
public:
    using GraphElement = std::pair <int, GraphEdge::GraphEdgeIndex>;
    using ElementQueue = std::queue <GraphElement>;

    GraphAlgorithm();

    ElementQueue getSequence() const;
    bool emptySequence() const;
    GraphAlgorithm::GraphElement getNextElement();
    GraphAlgorithm::GraphElement getLastElement() const;

    void pushNode(int nodeIndex);
    void pushEdge(GraphEdge::GraphEdgeIndex edgeIndex);

    virtual void operator() (const Graph& graph) = 0;

private:
    GraphAlgorithm::ElementQueue sequence;
};

class PrimAlgorithm : public GraphAlgorithm
{
public:
    PrimAlgorithm();
    ~PrimAlgorithm();

    void operator() (const Graph& graph);

private:
    void addElementToMST(const Graph& graph, int node, int &lastNode, int parent = -1);

    Graph* MST;
};
