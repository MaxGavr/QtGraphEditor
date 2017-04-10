#include "graph.h"

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

GraphNode::const_reference Graph::addNode(QString idtf)
{
    GraphNode* newNode;
    if (idtf.isEmpty())
        newNode = new GraphNode(setNodeIndex());
    else
        newNode = new GraphNode(setNodeIndex(), idtf);
    nodes.append(newNode);
    return *newNode;
}

GraphNode::const_reference Graph::addNode(int index, QString idtf)
{
    if (validateNodeIndex(index))
    {
        GraphNode* newNode;
        if (idtf.isEmpty())
            newNode = new GraphNode(index);
        else
            newNode = new GraphNode(index, idtf);
        nodes.append(newNode);
        return *newNode;
    }
    else
        throw bad_graph_node();
}

void Graph::removeNode(GraphNode::const_reference node)
{
    GraphNode* node_ptr = findNodeByIndex(node.getIndex());
    removeNodeIndex(node.getIndex());
    nodes.removeOne(node_ptr);
    delete node_ptr;
}

void Graph::setNodeIdtf(GraphNode::const_reference node, QString idtf)
{
    GraphNode* node_ptr = findNodeByIndex(node.getIndex());
    if (node_ptr)
        node_ptr->setText(idtf);
}

GraphEdge::const_reference Graph::addEdge(GraphNode::const_reference firstNode,
                                          GraphNode::const_reference secondNode,
                                          int weight)
{
    if (!containsEdge(firstNode, secondNode) && (firstNode != secondNode))
    {
        GraphEdge* newEdge = new GraphEdge(findNodeByIndex(firstNode.getIndex()),
                                           findNodeByIndex(secondNode.getIndex()), weight);
        edges.append(newEdge);
        return *newEdge;
    }
    else
        throw bad_graph_edge();
}

GraphEdge::const_reference Graph::addEdge(int firstIndex, int secondIndex, int weight)
{
    GraphNode* firstNode = findNodeByIndex(firstIndex);
    GraphNode* secondNode = findNodeByIndex(secondIndex);

    if (firstNode && secondNode)
        return addEdge(*firstNode, *secondNode, weight);
    else
        throw bad_graph_edge();
}

GraphNode* Graph::findNodeByIndex(int index)
{
    foreach (GraphNode* node, nodes)
        if (node->getIndex() == index)
            return node;
    return NULL;
}

GraphEdge* Graph::findEdgeByIndex(const GraphEdge::GraphEdgeIndex &index)
{
    foreach (GraphEdge* edge, edges)
        if (edge->getEdgeIndex() == index)
            return edge;
    return NULL;
}

void Graph::removeEdge(GraphEdge::const_reference edge)
{
    GraphEdge* edge_ptr = findEdgeByIndex(edge.getEdgeIndex());
    edges.removeOne(edge_ptr);
    delete edge_ptr;
}

void Graph::setEdgeWeight(GraphEdge::const_reference edge, int weight)
{
    GraphEdge* edge_ptr = findEdgeByIndex(edge.getEdgeIndex());
    if (edge_ptr)
        edge_ptr->setWeight(weight);
}

bool Graph::containsEdge(GraphNode::const_reference firstNode, GraphNode::const_reference secondNode) const
{
    GraphEdge::GraphEdgeIndex edgeIndex(firstNode.getIndex(), secondNode.getIndex());
    foreach (GraphEdge* edge, edges)
    {
        if (edge->getEdgeIndex() == edgeIndex)
            return true;
    }
    return NULL;
}

int Graph::setNodeIndex()
{
    int i = 0;
    while (!validateNodeIndex(i))
        i++;
    nodeIndices.push_back(i);
    return i;
}

void Graph::removeNodeIndex(int i)
{
    nodeIndices.removeOne(i);
}

bool Graph::validateNodeIndex(int i) const
{
    if (i < 0 || nodeIndices.contains(i))
        return false;
    else
        return true;
}

bool Graph::validateEdgeIndex(GraphEdge::GraphEdgeIndex i)
{
    if (!validateNodeIndex(i.first) || !validateNodeIndex(i.second))
        return false;
    else
        return true;
}

