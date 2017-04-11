#include "graphalgorithm.h"
#include <queue>
#include <vector>

GraphAlgorithm::GraphAlgorithm()
{

}

PrimAlgorithm::PrimAlgorithm()
{
    MST = new Graph();
}

PrimAlgorithm::~PrimAlgorithm()
{
    delete MST;
}

void PrimAlgorithm::operator()(const Graph &graph)
{

    using IPair = std::pair<unsigned int, int>;
    const unsigned int INF = std::numeric_limits<int>::max() + 1;

    Graph::AdjacencyList adjList = graph.getAdjacencyList();
    int nodesNumber = graph.countNodes();

    std::priority_queue< IPair, std::vector <IPair> , std::greater<IPair> > queue;
    std::vector<int> keys(nodesNumber, INF);
    std::vector<int> parent(nodesNumber, -1);
    std::vector<bool> included(nodesNumber, false);

    int startNode = 0;
    queue.push(std::make_pair(0, startNode));
    keys[startNode] = 0;

    while (!queue.empty())
    {
        int minKeyNode = queue.top().second;
        queue.pop();

        included[minKeyNode] = true;
        GraphNode::const_reference newNode = MST->addNode(graph.retrieveNode(minKeyNode));
        if (parent[minKeyNode] != -1)
        {
            GraphNode::const_reference parentNode = graph.retrieveNode(parent[minKeyNode]);
            MST->addEdge(newNode, parentNode);
        }

        QPair<int, int> adjacent;
        foreach (adjacent, adjList[minKeyNode])
        {
            int v = adjacent.second;
            int weight = adjacent.first;

            if (!included[v] && (keys[v] > weight))
            {
                keys[v] = weight;
                queue.push(std::make_pair(keys[v], v));
                parent[v] = minKeyNode;
            }
        }
    }

    for (int i = 1; i < nodesNumber; ++i)
        qInfo("%d - %d", parent[i], i);
}
