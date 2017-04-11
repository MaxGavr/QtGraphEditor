#pragma once

#include "graph/graph.h"

class GraphAlgorithm
{
public:
    GraphAlgorithm();

    virtual void operator() (const Graph& graph) = 0;
};

class PrimAlgorithm : public GraphAlgorithm
{
public:
    PrimAlgorithm();
    ~PrimAlgorithm();
    void operator() (const Graph& graph);

private:
    Graph* MST;
};
