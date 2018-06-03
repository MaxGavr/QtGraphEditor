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

    class Arguments
    {
    public:
        Arguments();
        ~Arguments();

        Graph* graph;
        Node::Index startNode;
    };

    class Result
    {
    public:
        Result();
        ~Result();

        void setBool(bool result);
        void setInt(int result);
        void setGraph(Graph* result);

        bool isBool() const;
        bool isInt() const;
        bool isGraph() const;

        bool getBool() const;
        int getInt() const;
        Graph* getGraph() const;

    private:
        bool boolResult;
        bool hasBool;

        int intResult;
        bool hasInt;

        Graph* graphResult;
        bool hasGraph;
    };


    GraphAlgorithm();

    ElementQueue getSequence() const;
    bool emptySequence() const;
    GraphAlgorithm::GraphElement getNextElement();
    GraphAlgorithm::GraphElement getLastElement() const;

    void pushNode(Node::Index nodeIndex);
    void pushEdge(Edge::Index edgeIndex);

    virtual Result execute(Arguments args) = 0;

private:
    GraphAlgorithm::ElementQueue sequence;
};


class PrimAlgorithm : public GraphAlgorithm
{
public:
    PrimAlgorithm();
    ~PrimAlgorithm();

    Result execute(Arguments args) override;

private:
    void addElementToMST(const Graph& graph, int node, int &lastNode, int parent = -1);

    Graph* MST;
};

class EulerianGraphAlgorithm : public GraphAlgorithm
{
public:
    EulerianGraphAlgorithm();
    ~EulerianGraphAlgorithm();

    Result execute(Arguments args) override;
};

class HamiltonianCycleAlgorithm : public GraphAlgorithm
{
public:
    HamiltonianCycleAlgorithm();
    ~HamiltonianCycleAlgorithm();

    Result execute(Arguments args) override;

private:
    bool findHamiltonianCycle(const Graph& graph, std::vector<Node::Index>& cycle);
};

class GraphRadiusAlgorithm : public GraphAlgorithm
{
public:
    GraphRadiusAlgorithm();
    ~GraphRadiusAlgorithm();

    Result execute(Arguments args) override;
};

class GraphDiameterAlgorithm : public GraphAlgorithm
{
public:
    GraphDiameterAlgorithm();
    ~GraphDiameterAlgorithm();

    Result execute(Arguments args) override;
};

}
