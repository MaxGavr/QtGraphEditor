#pragma once

#include <QString>
#include <QLinkedList>
#include <QPair>

class GraphEdge;


class GraphNode
{
    friend class Graph;
    friend class GraphEdge;

public:
    using const_ref = const GraphNode&;

    GraphNode(int i);
    GraphNode(int i, const QString& str);
    ~GraphNode();

    int getIndex() const;

    QString getText() const;
    void setText(const QString& str);

    QList<QPair<int, int> > getAdjacentNodes() const;

    friend bool operator== (GraphNode::const_ref first, GraphNode::const_ref second);
    friend bool operator!= (GraphNode::const_ref first, GraphNode::const_ref second);

private:
    void setIndex(int i);
    void addEdge(GraphEdge* edge);
    void removeEdge(GraphEdge* edge);

    int index;
    QString text;
    QLinkedList<GraphEdge*> edges;
};

bool operator== (GraphNode::const_ref first, GraphNode::const_ref second);
bool operator!= (GraphNode::const_ref first, GraphNode::const_ref second);
