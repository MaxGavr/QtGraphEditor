#include "graph.h"

Graph::Graph()
{

}

GraphNode::const_reference Graph::addNode()
{
    return addNode(QString());
}

GraphNode::const_reference Graph::addNode(QString nodeText)
{
    GraphNode* newNode = new GraphNode(setNodeIndex(), nodeText);
    nodes.append(newNode);
    return *newNode;
}

void Graph::removeNode(const GraphNode& node)
{
    GraphNode* node_ptr = findNodeByIndex(node.getIndex());
    removeNodeIndex(node.getIndex());
    nodes.removeOne(node_ptr);
    delete node_ptr;
}

GraphEdge* Graph::addEdge(const GraphNode& firstNode, const GraphNode& secondNode)
{
    GraphEdge* newEdge = new GraphEdge(findNodeByIndex(firstNode.getIndex()),
                                       findNodeByIndex(secondNode.getIndex()));
    edges.append(newEdge);
    return newEdge;
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
        if (edge->getStartNode()->getIndex() == index.first &&
            edge->getEndNode()->getIndex() == index.second)
            return edge;
    return NULL;
}

void Graph::removeEdge(const GraphEdge& edge)
{
    GraphEdge* edge_ptr = findEdgeByIndex(edge.getEdgeIndex());
    edges.removeOne(edge_ptr);
    delete edge_ptr;
}

int Graph::setNodeIndex()
{
    int i = 0;
    while (nodeIndices.contains(i))
        i++;
    nodeIndices.push_back(i);
    return i;
}

void Graph::removeNodeIndex(int i)
{
    nodeIndices.removeOne(i);
}

