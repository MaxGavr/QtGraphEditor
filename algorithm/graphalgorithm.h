#pragma once

#include "graph/graph.h"

class GraphAlgorithm
{
public:
    using GraphElement = std::pair <int, GraphEdge::GraphEdgeIndex>;
    using ElementQueue = std::queue <GraphElement>;

    GraphAlgorithm();

    virtual void operator() (const Graph& graph) = 0;
};

class PrimAlgorithm : public GraphAlgorithm
{
public:
    PrimAlgorithm();
    ~PrimAlgorithm();

    ElementQueue getSequence() const;
    bool emptySequence() const;
    GraphAlgorithm::GraphElement getNextElement();

    void operator() (const Graph& graph);

private:
    GraphAlgorithm::ElementQueue sequence;
    Graph* MST;
};
