#pragma once

#include <queue>

#include "graph/graph.h"


namespace GraphModel
{

class GraphAlgorithm
{
public:
    using GraphElement = std::pair <int, Edge::Index>;
    using ElementQueue = std::queue <GraphElement>;

    GraphAlgorithm();

    ElementQueue getSequence() const;
    bool emptySequence() const;
    GraphAlgorithm::GraphElement getNextElement();
    GraphAlgorithm::GraphElement getLastElement() const;

    void pushNode(int nodeIndex);
    void pushEdge(Edge::Index edgeIndex);

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

    Graph* getMST() const;

private:
    void addElementToMST(const Graph& graph, int node, int &lastNode, int parent = -1);

    Graph* MST;
};

class EulerianGraphAlgorithm : public GraphAlgorithm
{
public:
    EulerianGraphAlgorithm();
    ~EulerianGraphAlgorithm();

    void execute(const Graph& graph) override;

    bool isEulerian() const;

private:
    bool isEulerianGraph;
};

}
