#include "graphalgorithm.h"
#include <vector>

using namespace GraphModel;


GraphAlgorithm::Arguments::Arguments()
    : graph(nullptr), startNode(-1)
{
}

GraphAlgorithm::Arguments::~Arguments()
{
}


GraphAlgorithm::Result::Result()
    : boolResult(false), hasBool(false),
      intResult(0), hasInt(false),
      graphResult(nullptr), hasGraph(false)
{
}

GraphAlgorithm::Result::~Result()
{
    //if (hasGraph)
        //delete graphResult;
}

void GraphAlgorithm::Result::setBool(bool result)
{
    boolResult = result;
    hasBool = true;
}

void GraphAlgorithm::Result::setInt(int result)
{
    intResult = result;
    hasInt = true;
}

void GraphAlgorithm::Result::setGraph(Graph* result)
{
    if (hasGraph)
        delete graphResult;

    graphResult = result;
    hasGraph = true;
}

bool GraphAlgorithm::Result::isBool() const
{
    return hasBool;
}

bool GraphAlgorithm::Result::isInt() const
{
    return hasInt;
}

bool GraphAlgorithm::Result::isGraph() const
{
    return hasGraph;
}

bool GraphAlgorithm::Result::getBool() const
{
    return boolResult;
}

int GraphAlgorithm::Result::getInt() const
{
    return intResult;
}

Graph* GraphAlgorithm::Result::getGraph() const
{
    return graphResult;
}


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
}

PrimAlgorithm::~PrimAlgorithm()
{
}

GraphAlgorithm::Result PrimAlgorithm::execute(Arguments args)
{
    Result result;

    if (args.graph == nullptr)
        return result;

    const Graph& graph = *(args.graph);

    if (graph.isEmpty())
        return result;

    MST = new Graph();

    using IPair = std::pair<unsigned int, int>;
    const int INF = std::numeric_limits<int>::max();

    Graph::AdjacencyList adjList = graph.getAdjacencyList();
    int nodesNumber = graph.countNodes();

    std::priority_queue< IPair, std::vector <IPair> , std::greater<IPair> > queue;
    std::vector<int> keys(nodesNumber, INF);
    std::vector<int> parent(nodesNumber, -1);
    std::vector<bool> included(nodesNumber, false);

    bool weighted = graph.isWeighted();
    std::vector<int> distance(nodesNumber, 0);

    Node::Index startNode = args.startNode;
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

            if (!included[v] && keys[v] > weight)
            {
                keys[v] = weight;
                queue.push(std::make_pair(keys[v], v));
                parent[v] = minKeyNode;

                if (weighted)
                    distance[v] = distance[minKeyNode] + weight;
                else
                    distance[v] = distance[minKeyNode] + 1;
            }
        }
    }

    result.setGraph(MST);
    result.setInt(*(std::max_element(distance.begin(), distance.end())));

    return result;
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
{
}

EulerianGraphAlgorithm::~EulerianGraphAlgorithm()
{
}

GraphAlgorithm::Result EulerianGraphAlgorithm::execute(Arguments args)
{
    Result result;

    if (args.graph == nullptr)
        return result;

    Graph& graph = *(args.graph);

    Graph::Type type = graph.getType();

    // can not check if graph is eulerian if it is empty or contains both arcs and edges
    if (type == Graph::Empty || type == Graph::Mixed)
    {
        result.setBool(false);
        return result;
    }

    // unoriented graph should not contain nodes with odd degree
    if (type == Graph::Unoriented)
    {
        for (int node = 0; node < graph.countNodes(); ++node)
        {
            int degree = graph.retrieveNode(node).getDegree();
            if (degree % 2 == 1)
            {
                result.setBool(false);
                return result;
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
                result.setBool(false);
                return result;
            }
        }
    }

    // check graph for connectivity
    PrimAlgorithm prim;
    Arguments primArgs;
    primArgs.graph = &graph;
    primArgs.startNode = 0;

    Result primResult = prim.execute(primArgs);

    if (primResult.getGraph()->countNodes() != graph.countNodes())
    {
        result.setBool(false);
        return result;
    }

    result.setBool(true);
    return result;
}


HamiltonianCycleAlgorithm::HamiltonianCycleAlgorithm()
{
}

HamiltonianCycleAlgorithm::~HamiltonianCycleAlgorithm()
{
}

GraphAlgorithm::Result HamiltonianCycleAlgorithm::execute(Arguments args)
{
    Result result;

    if (args.graph == nullptr)
        return result;

    const Graph& graph = *(args.graph);

    if (graph.isEmpty())
        return result;

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

    return result;
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


GraphRadiusAlgorithm::GraphRadiusAlgorithm()
{
}

GraphRadiusAlgorithm::~GraphRadiusAlgorithm()
{
}

GraphAlgorithm::Result GraphRadiusAlgorithm::execute(GraphAlgorithm::Arguments args)
{
    Result result;

    if (args.graph->isEmpty())
    {
        result.setInt(0);
        return result;
    }

    int minEccentricity = 1;

    PrimAlgorithm prim;
    Arguments primArgs;
    primArgs.graph = args.graph;
    Result primResult;

    for (Node::Index node = 0; node < args.graph->countNodes(); ++node)
    {
        primArgs.startNode = node;
        primResult = prim.execute(primArgs);

        minEccentricity = std::min(minEccentricity, primResult.getInt());
    }

    result.setInt(minEccentricity);
    return result;
}


GraphDiameterAlgorithm::GraphDiameterAlgorithm()
{
}

GraphDiameterAlgorithm::~GraphDiameterAlgorithm()
{
}

GraphAlgorithm::Result GraphDiameterAlgorithm::execute(GraphAlgorithm::Arguments args)
{
    Result result;

    int maxEccentricity = 0;

    PrimAlgorithm prim;
    Arguments primArgs;
    primArgs.graph = args.graph;
    Result primResult;

    for (Node::Index node = 0; node < args.graph->countNodes(); ++node)
    {
        primArgs.startNode = node;
        primResult = prim.execute(primArgs);

        maxEccentricity = std::max(maxEccentricity, primResult.getInt());
    }

    result.setInt(maxEccentricity);
    return result;
}


GraphCenterAlgorithm::GraphCenterAlgorithm()
{
}

GraphCenterAlgorithm::~GraphCenterAlgorithm()
{
}

GraphAlgorithm::Result GraphCenterAlgorithm::execute(GraphAlgorithm::Arguments args)
{
    Result result;

    GraphRadiusAlgorithm radiusAlgo;
    Arguments radiusArgs;
    radiusArgs.graph = args.graph;
    Result radiusResult;

    PrimAlgorithm primAlgo;
    Arguments primArgs;
    primArgs.graph = args.graph;
    Result primResult;

    for (Node::Index node = 0; node < args.graph->countNodes(); ++node)
    {
        radiusArgs.startNode = node;
        radiusResult = radiusAlgo.execute(radiusArgs);

        primArgs.startNode = node;
        primResult = primAlgo.execute(primArgs);

        if (radiusResult.getInt() == primResult.getInt())
            pushNode(node);
    }

    return result;
}
