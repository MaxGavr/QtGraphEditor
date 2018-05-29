#include <queue>

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

GraphNode::const_ref Graph::addNode(QString idtf)
{
    GraphNode* newNode;
    if (idtf.isEmpty())
        newNode = new GraphNode(setNodeIndex());
    else
        newNode = new GraphNode(setNodeIndex(), idtf);
    nodes.append(newNode);
    return *newNode;
}

GraphNode::const_ref Graph::addNode(GraphNode::Index index, QString idtf)
{
    if (validateNodeIndex(index))
    {
        nodeIndices.insert(index);
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

GraphNode::const_ref Graph::addNode(GraphNode::const_ref node)
{
    return addNode(node.getText());
}

void Graph::removeNode(GraphNode::const_ref node)
{
    GraphNode* node_ptr = findNodeByIndex(node.getIndex());
    removeNodeIndex(node.getIndex());
    nodes.removeOne(node_ptr);
    delete node_ptr;
}

void Graph::setNodeIdtf(GraphNode::const_ref node, QString idtf)
{
    GraphNode* node_ptr = findNodeByIndex(node.getIndex());
    if (node_ptr)
        node_ptr->setText(idtf);
}

GraphEdge::const_ref Graph::addEdge(GraphNode::const_ref firstNode,
                                          GraphNode::const_ref secondNode,
                                          int weight,
                                          bool oriented)
{
    if (!containsEdge(firstNode, secondNode))
    {
        GraphEdge* newEdge = new GraphEdge(findNodeByIndex(firstNode.getIndex()),
                                           findNodeByIndex(secondNode.getIndex()),
                                           weight,
                                           oriented);
        edges.append(newEdge);
        return *newEdge;
    }
    else
        throw bad_graph_edge();
}

GraphEdge::const_ref Graph::addEdge(GraphNode::Index firstIndex, GraphNode::Index secondIndex, int weight, bool oriented)
{
    GraphNode* firstNode = findNodeByIndex(firstIndex);
    GraphNode* secondNode = findNodeByIndex(secondIndex);

    if (firstNode && secondNode)
        return addEdge(*firstNode, *secondNode, weight, oriented);
    else
        throw bad_graph_edge();
}

GraphNode* Graph::findNodeByIndex(GraphNode::Index index)
{
    foreach (GraphNode* node, nodes)
        if (node->getIndex() == index)
            return node;
    return NULL;
}

GraphEdge* Graph::findEdgeByIndex(const GraphEdge::Index &index)
{
    foreach (GraphEdge* edge, edges)
        if (edge->getIndex() == index)
            return edge;
    return NULL;
}

void Graph::removeEdge(GraphEdge::const_ref edge)
{
    GraphEdge* edge_ptr = findEdgeByIndex(edge.getIndex());
    edges.removeOne(edge_ptr);
    delete edge_ptr;
}

void Graph::setEdgeWeight(GraphEdge::const_ref edge, int weight)
{
    GraphEdge* edge_ptr = findEdgeByIndex(edge.getIndex());
    if (edge_ptr)
        edge_ptr->setWeight(weight);
}

bool Graph::containsEdge(GraphNode::const_ref firstNode, GraphNode::const_ref secondNode) const
{
    GraphEdge::Index edgeIndex(firstNode.getIndex(), secondNode.getIndex());
    foreach (GraphEdge* edge, edges)
    {
        if (edge->getIndex() == edgeIndex)
            return true;
    }
    return NULL;
}

GraphNode::const_ref Graph::retrieveNode(GraphNode::Index index) const
{
    foreach (GraphNode* node, nodes)
        if (node->getIndex() == index)
            return *node;
    throw bad_graph_node();
}

GraphEdge::const_ref Graph::retrieveEdge(GraphEdge::Index index) const
{
    foreach (GraphEdge* edge, edges)
        if (edge->getIndex() == index)
            return *edge;
    throw bad_graph_edge();
}

bool Graph::isEmpty() const
{
    return countNodes() == 0;
}

int Graph::countNodes() const
{
    return nodes.size();
}

int Graph::countEdges() const
{
    return edges.size();
}

QList<GraphEdge::Index> Graph::getEdges() const
{
    QList<GraphEdge::Index> edgeIndices;

    foreach (GraphEdge* edge, edges)
        edgeIndices.append(edge->getIndex());

    return edgeIndices;
}

Graph::AdjacencyList Graph::getAdjacencyList() const
{
    AdjacencyList list;
    foreach (GraphNode::Index nodeIndex, nodeIndices)
    {
        GraphNode::const_ref node = retrieveNode(nodeIndex);
        QList< QPair<int, GraphNode::Index> > adjacentNodes = node.getAdjacentNodes();
        list.insert(node.getIndex(), adjacentNodes);
    }
    return list;
}

int Graph::setNodeIndex()
{
    GraphNode::Index i = 0;
    while (!validateNodeIndex(i))
        i++;
    nodeIndices.insert(i);
    return i;
}

void Graph::removeNodeIndex(GraphNode::Index i)
{
    std::set<GraphNode::Index>::iterator erased = nodeIndices.erase(nodeIndices.find(i));

    std::set<GraphNode::Index> shiftedIndices;
    for (std::set<GraphNode::Index>::iterator it = erased; it != nodeIndices.end(); it++)
    {
        GraphNode::Index index = *it;
        findNodeByIndex(index)->setIndex(index - 1);
        shiftedIndices.insert(index - 1);
    }
    nodeIndices.erase(erased, nodeIndices.end());
    nodeIndices.insert(shiftedIndices.begin(), shiftedIndices.end());
}

bool Graph::validateNodeIndex(GraphNode::Index i) const
{
     return !((i < 0) || (nodeIndices.find(i) != nodeIndices.end()));

}

bool Graph::validateEdgeIndex(GraphEdge::Index i)
{
    return !validateNodeIndex(i.first) || !validateNodeIndex(i.second);
}

