#include <queue>

#include "graph.h"

using namespace GraphModel;


Graph::Graph()
{
}

Graph::~Graph()
{
    qDeleteAll(edges);
    edges.clear();
    qDeleteAll(nodes);
    nodes.clear();
}

Node::const_ref Graph::addNode(QString idtf)
{
    Node* newNode;
    if (idtf.isEmpty())
        newNode = new Node(setNodeIndex());
    else
        newNode = new Node(setNodeIndex(), idtf);
    nodes.append(newNode);
    return *newNode;
}

Node::const_ref Graph::addNode(Node::Index index, QString idtf)
{
    if (validateNodeIndex(index))
    {
        nodeIndices.insert(index);
        Node* newNode;
        if (idtf.isEmpty())
            newNode = new Node(index);
        else
            newNode = new Node(index, idtf);
        nodes.append(newNode);
        return *newNode;
    }
    else
        throw bad_graph_node();
}

Node::const_ref Graph::addNode(Node::const_ref node)
{
    return addNode(node.getText());
}

void Graph::removeNode(Node::const_ref node)
{
    Node* node_ptr = findNodeByIndex(node.getIndex());
    removeNodeIndex(node.getIndex());
    nodes.removeOne(node_ptr);
    delete node_ptr;
}

void Graph::setNodeIdtf(Node::const_ref node, QString idtf)
{
    Node* node_ptr = findNodeByIndex(node.getIndex());
    if (node_ptr)
        node_ptr->setText(idtf);
}

Edge::const_ref Graph::addEdge(Node::const_ref firstNode,
                                          Node::const_ref secondNode,
                                          int weight,
                                          bool oriented)
{
    if (!containsEdge(firstNode, secondNode))
    {
        Edge* newEdge = new Edge(findNodeByIndex(firstNode.getIndex()),
                                           findNodeByIndex(secondNode.getIndex()),
                                           weight,
                                           oriented);
        edges.append(newEdge);
        return *newEdge;
    }
    else
        throw bad_graph_edge();
}

Edge::const_ref Graph::addEdge(Node::Index firstIndex, Node::Index secondIndex, int weight, bool oriented)
{
    Node* firstNode = findNodeByIndex(firstIndex);
    Node* secondNode = findNodeByIndex(secondIndex);

    if (firstNode && secondNode)
        return addEdge(*firstNode, *secondNode, weight, oriented);
    else
        throw bad_graph_edge();
}

Node* Graph::findNodeByIndex(Node::Index index)
{
    foreach (Node* node, nodes)
        if (node->getIndex() == index)
            return node;
    return NULL;
}

Edge* Graph::findEdgeByIndex(const Edge::Index &index)
{
    foreach (Edge* edge, edges)
        if (edge->getIndex() == index)
            return edge;
    return NULL;
}

void Graph::removeEdge(Edge::const_ref edge)
{
    Edge* edge_ptr = findEdgeByIndex(edge.getIndex());
    edges.removeOne(edge_ptr);
    delete edge_ptr;
}

void Graph::setEdgeWeight(Edge::const_ref edge, int weight)
{
    Edge* edge_ptr = findEdgeByIndex(edge.getIndex());
    if (edge_ptr)
        edge_ptr->setWeight(weight);
}

bool Graph::containsEdge(Node::const_ref firstNode, Node::const_ref secondNode) const
{
    Edge::Index edgeIndex(firstNode.getIndex(), secondNode.getIndex());
    foreach (Edge* edge, edges)
    {
        if (edge->getIndex() == edgeIndex)
        {
            if (edge->isOriented())
                return edge->getIndex().first == edgeIndex.first;
            else
                return true;
        }
    }
    return NULL;
}

Node::const_ref Graph::retrieveNode(Node::Index index) const
{
    foreach (Node* node, nodes)
        if (node->getIndex() == index)
            return *node;
    throw bad_graph_node();
}

Edge::const_ref Graph::retrieveEdge(Edge::Index index) const
{
    foreach (Edge* edge, edges)
        if (edge->getIndex() == index)
            return *edge;
    throw bad_graph_edge();
}

bool Graph::isEmpty() const
{
    return countNodes() == 0;
}

Graph::Type Graph::getType() const
{
    bool hasArcs = false;
    bool hasEdges = false;

    foreach (Edge* edge, edges) {
        if (edge->isOriented())
            hasArcs = true;
        else
            hasEdges = true;
    }

    if (hasArcs && hasEdges)
        return Type::Mixed;
    else if (hasArcs)
        return Type::Oriented;
    else if (hasEdges)
        return Type::Unoriented;
    else
        return Type::Empty;
}

bool Graph::isWeighted() const
{
    foreach (Edge* edge, edges)
        if (edge->getWeight() != 0)
            return true;

    return false;
}

int Graph::countNodes() const
{
    return nodes.size();
}

int Graph::countEdges() const
{
    return edges.size();
}

QList<Edge::Index> Graph::getEdges() const
{
    QList<Edge::Index> edgeIndices;

    foreach (Edge* edge, edges)
        edgeIndices.append(edge->getIndex());

    return edgeIndices;
}

Graph::AdjacencyList Graph::getAdjacencyList() const
{
    AdjacencyList list;
    foreach (Node::Index nodeIndex, nodeIndices)
    {
        Node::const_ref node = retrieveNode(nodeIndex);
        QList< QPair<int, Node::Index> > adjacentNodes = node.getAdjacentNodes();
        list.insert(node.getIndex(), adjacentNodes);
    }
    return list;
}

int Graph::setNodeIndex()
{
    Node::Index i = 0;
    while (!validateNodeIndex(i))
        i++;
    nodeIndices.insert(i);
    return i;
}

void Graph::removeNodeIndex(Node::Index i)
{
    std::set<Node::Index>::iterator erased = nodeIndices.erase(nodeIndices.find(i));

    std::set<Node::Index> shiftedIndices;
    for (std::set<Node::Index>::iterator it = erased; it != nodeIndices.end(); it++)
    {
        Node::Index index = *it;
        findNodeByIndex(index)->setIndex(index - 1);
        shiftedIndices.insert(index - 1);
    }
    nodeIndices.erase(erased, nodeIndices.end());
    nodeIndices.insert(shiftedIndices.begin(), shiftedIndices.end());
}

bool Graph::validateNodeIndex(Node::Index i) const
{
     return !((i < 0) || (nodeIndices.find(i) != nodeIndices.end()));

}

bool Graph::validateEdgeIndex(Edge::Index i)
{
    return !validateNodeIndex(i.first) || !validateNodeIndex(i.second);
}

