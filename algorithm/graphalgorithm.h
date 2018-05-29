#pragma once

#include <queue>

#include "graph/graph.h"


class GraphAlgorithm
{
public:
    using GraphElement = std::pair <int, GraphEdge::Index>;
    using ElementQueue = std::queue <GraphElement>;

    GraphAlgorithm();

    ElementQueue getSequence() const;
    bool emptySequence() const;
    GraphAlgorithm::GraphElement getNextElement();
    GraphAlgorithm::GraphElement getLastElement() const;

    void pushNode(int nodeIndex);
    void pushEdge(GraphEdge::Index edgeIndex);

    virtual void execute(const Graph& graph) = 0;

private:
    GraphAlgorithm::ElementQueue sequence;
};

class PrimAlgorithm : public GraphAlgorithm
{
public:
    PrimAlgorithm();
    ~PrimAlgorithm();

    void execute(const Graph& graph);

private:
    void addElementToMST(const Graph& graph, int node, int &lastNode, int parent = -1);

    Graph* MST;
};
