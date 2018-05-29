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

void GraphAlgorithm::pushNode(int nodeIndex)
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
