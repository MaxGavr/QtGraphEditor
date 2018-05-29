#pragma once

#include <QString>
#include <QLinkedList>
#include <QPair>

class GraphEdge;


class GraphNode
{
public:
    using const_ref = const GraphNode&;
    using Index = int;
    using AdjacentNodes = QList< QPair<int, GraphNode::Index> >;

    GraphNode(GraphNode::Index i);
    GraphNode(GraphNode::Index i, const QString& str);
    ~GraphNode();

    GraphNode::Index getIndex() const;

    QString getText() const;
    void setText(const QString& str);

    AdjacentNodes getAdjacentNodes() const;

    friend bool operator== (GraphNode::const_ref first, GraphNode::const_ref second);
    friend bool operator!= (GraphNode::const_ref first, GraphNode::const_ref second);

private:
    void setIndex(GraphNode::Index i);
    void addEdge(GraphEdge* edge);
    void removeEdge(GraphEdge* edge);

    GraphNode::Index index;
    QString text;
    QLinkedList<GraphEdge*> edges;

    friend class Graph;
    friend class GraphEdge;
};

bool operator== (GraphNode::const_ref first, GraphNode::const_ref second);
bool operator!= (GraphNode::const_ref first, GraphNode::const_ref second);
