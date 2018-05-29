#pragma once

#include <QVector>
#include <QMap>
#include <set>

#include "graphedge.h"
#include "exceptions.h"


namespace GraphModel
{

class Graph
{
public:
    using AdjacencyList = QMap<Node::Index, Node::AdjacentNodes>;

    Graph();
    ~Graph();

    Node::const_ref addNode(QString idtf = "");
    Node::const_ref addNode(Node::Index index, QString idtf = "");
    Node::const_ref addNode(Node::const_ref node);

    Edge::const_ref addEdge(Node::const_ref firstNode,
                                 Node::const_ref secondNode,
                                 int weight = 0, bool oriented = false);
    Edge::const_ref addEdge(Node::Index firstIndex, Node::Index secondIndex, int weight = 0, bool oriented = false);

    void removeEdge(Edge::const_ref edge);
    void removeNode(Node::const_ref node);

    void setNodeIdtf(Node::const_ref node, QString idtf);
    void setEdgeWeight(Edge::const_ref edge, int weight);

    bool containsNode(Node::const_ref node) const;
    bool containsEdge(Node::const_ref firstNode,
                      Node::const_ref secondNode) const;

    Node::const_ref retrieveNode(Node::Index index) const;
    Edge::const_ref retrieveEdge(Edge::Index index) const;

    bool isEmpty() const;

    int countNodes() const;
    int countEdges() const;

    QList<Edge::Index> getEdges() const;

    AdjacencyList getAdjacencyList() const;

private:
    Node* findNodeByIndex(Node::Index index);
    Edge* findEdgeByIndex(const Edge::Index& index);

    QLinkedList<Node *> nodes;
    QLinkedList<Edge *> edges;

    int setNodeIndex();
    void removeNodeIndex(Node::Index i);
    bool validateNodeIndex(Node::Index i) const;
    bool validateEdgeIndex(Edge::Index i);

    std::set<Node::Index> nodeIndices;
};

}
