#pragma once

#include <QString>
#include <QLinkedList>
#include <QPair>


namespace GraphModel
{

class Edge;


class Node
{
public:
    using const_ref = const Node&;
    using Index = int;
    using AdjacentNodes = QList< QPair<int, Node::Index> >;

    Node(Node::Index i);
    Node(Node::Index i, const QString& str);
    ~Node();

    Node::Index getIndex() const;

    QString getText() const;
    void setText(const QString& str);

    AdjacentNodes getAdjacentNodes() const;

    int getDegree() const;
    int getInputDegree() const;
    int getOutputDegree() const;

    friend bool operator== (Node::const_ref first, Node::const_ref second);
    friend bool operator!= (Node::const_ref first, Node::const_ref second);

private:
    void setIndex(Node::Index i);
    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);

    Node::Index index;
    QString text;
    QLinkedList<Edge*> edges;

    friend class Graph;
    friend class Edge;
};

bool operator== (Node::const_ref first, Node::const_ref second);
bool operator!= (Node::const_ref first, Node::const_ref second);

}
