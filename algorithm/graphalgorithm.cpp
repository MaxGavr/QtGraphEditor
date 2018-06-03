#include "graphalgorithm.h"
#include <vector>

using namespace GraphModel;


GraphAlgorithm::GraphAlgorithm()
{

}

GraphAlgorithm::ElementQueue GraphAlgorithm::getSequence() const
{
    return sequence;
}

bool GraphAlgorithm::emptySequence() const
{
    return sequence.empty();
}

GraphAlgorithm::GraphElement GraphAlgorithm::getNextElement()
{
    if (!emptySequence())
    {
        GraphAlgorithm::GraphElement next = sequence.front();
        sequence.pop();
        return next;
    }
    else
        return GraphAlgorithm::GraphElement(std::make_pair(-1, Edge::Index(-1, -1)));
}

GraphAlgorithm::GraphElement GraphAlgorithm::getLastElement() const
{
    return sequence.back();
}

void GraphAlgorithm::pushNode(Node::Index nodeIndex)
{
    GraphElement node(std::make_pair(nodeIndex, Edge::Index(-1, -1)));
    sequence.push(node);
}

void GraphAlgorithm::pushEdge(Edge::Index edgeIndex)
{
    GraphElement edge(std::make_pair(-1, edgeIndex));
    sequence.push(edge);
}

PrimAlgorithm::PrimAlgorithm()
{
    MST = new Graph();
}

PrimAlgorithm::~PrimAlgorithm()
{
    delete MST;
}

void PrimAlgorithm::execute(const Graph &graph)
{
    if (graph.isEmpty())
        return;

    using IPair = std::pair<unsigned int, int>;
    const int INF = std::numeric_limits<int>::max();

    Graph::AdjacencyList adjList = graph.getAdjacencyList();
    int nodesNumber = graph.countNodes();

    std::priority_queue< IPair, std::vector <IPair> , std::greater<IPair> > queue;
    std::vector<int> keys(nodesNumber, INF);
    std::vector<int> parent(nodesNumber, -1);
    std::vector<bool> included(nodesNumber, false);

    int startNode = 0;
    queue.push(std::make_pair(0, startNode));
    keys[startNode] = 0;

    int lastNodeInMST = -1;

    while (!queue.empty())
    {
        int minKeyNode = queue.top().second;
        queue.pop();

        if (!included[minKeyNode])
        {
            addElementToMST(graph, minKeyNode, lastNodeInMST, parent[minKeyNode]);
        }

        included[minKeyNode] = true;

        QPair<int, int> adjacent;
        foreach (adjacent, adjList[minKeyNode])
        {
            int v = adjacent.second;
            int weight = adjacent.first;

            if ((!included[v]) && (keys[v] > weight))
            {
                keys[v] = weight;
                queue.push(std::make_pair(keys[v], v));
                parent[v] = minKeyNode;
            }
        }
    }
}

Graph* PrimAlgorithm::getMST() const
{
    return MST;
}

void PrimAlgorithm::addElementToMST(const Graph& graph, int node, int& lastNode, int parent)
{
    Node::const_ref newNode = MST->addNode(graph.retrieveNode(node));
    if (parent != -1)
    {
        Node::const_ref parentNode = MST->retrieveNode(lastNode);
        MST->addEdge(newNode, parentNode);
        pushEdge(Edge::Index(node, parent));
    }
    lastNode = newNode.getIndex();
    pushNode(graph.retrieveNode(node).getIndex());
}


EulerianGraphAlgorithm::EulerianGraphAlgorithm()
    : isEulerianGraph(false)
{
}

EulerianGraphAlgorithm::~EulerianGraphAlgorithm()
{
}

void EulerianGraphAlgorithm::execute(const Graph& graph)
{
    Graph::Type type = graph.getType();

    // can not check if graph is eulerian if it is empty or contains both arcs and edges
    if (type == Graph::Empty || type == Graph::Mixed)
    {
        isEulerianGraph = false;
        return;
    }

    // unoriented graph should not contain nodes with odd degree
    if (type == Graph::Unoriented)
    {
        for (int node = 0; node < graph.countNodes(); ++node)
        {
            int degree = graph.retrieveNode(node).getDegree();
            if (degree % 2 == 1)
            {
                isEulerianGraph = false;
                return;
            }
        }
    }
    // oriented graph should not contain nodes with unequal input and output degrees
    else if (type == Graph::Oriented)
    {
        for (int node = 0; node < graph.countNodes(); ++node)
        {
            int inputDegree = graph.retrieveNode(node).getInputDegree();
            int outputDegree = graph.retrieveNode(node).getOutputDegree();

            if (inputDegree != outputDegree)
            {
                isEulerianGraph = false;
                return;
            }
        }
    }

    // check graph for connectivity
    PrimAlgorithm prim;
    prim.execute(graph);

    if (prim.getMST()->countNodes() != graph.countNodes())
    {
        isEulerianGraph = false;
        return;
    }

    isEulerianGraph = true;
}

bool EulerianGraphAlgorithm::isEulerian() const
{
    return isEulerianGraph;
}


HamiltonianCycleAlgorithm::HamiltonianCycleAlgorithm()
{
}

HamiltonianCycleAlgorithm::~HamiltonianCycleAlgorithm()
{
}

void HamiltonianCycleAlgorithm::execute(const Graph& graph)
{
    if (graph.isEmpty())
        return;

    std::vector<Node::Index> cycle;
    cycle.push_back(0);

    if (findHamiltonianCycle(graph, cycle))
    {
        for (size_t i = 0; i < cycle.size(); ++i)
        {
            Node::Index node = cycle[i];

            if (i == 0)
                pushNode(node);
            else
            {
                pushEdge(Edge::Index(cycle[i - 1], node));
                pushNode(node);
            }
        }

        pushEdge(Edge::Index(cycle.back(), cycle.front()));
    }
}

bool HamiltonianCycleAlgorithm::findHamiltonianCycle(const Graph& graph, std::vector<Node::Index>& cycle)
{
    if (cycle.size() == graph.countNodes())
    {
        Node::Index lastNode = cycle.back();
        Node::Index firstNode = cycle.front();

        if (graph.containsEdge(graph.retrieveNode(lastNode), graph.retrieveNode(firstNode)))
            return true;
        else
            return false;
    }

    const Node& currentNode = graph.retrieveNode(cycle.back());

    QPair<int, Node::Index> adjacentNode;
    foreach (adjacentNode, currentNode.getAdjacentNodes())
    {
        if (std::find(cycle.begin(), cycle.end(), adjacentNode.second) != cycle.end())
            continue;

        cycle.push_back(adjacentNode.second);

        if (findHamiltonianCycle(graph, cycle))
            return true;

        cycle.pop_back();
    }

    return false;
}
