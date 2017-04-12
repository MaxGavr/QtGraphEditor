#pragma once

#include <QString>
#include <QList>
#include <QLinkedList>
#include <QtAlgorithms>

#include "graphedge.h"



class GraphNode
{
    friend class Graph;
    friend class GraphEdge;

public:
    typedef const GraphNode& const_reference;

    GraphNode(int i);
    GraphNode(int i, const QString& str);
    ~GraphNode();

    int getIndex() const;

    QString getText() const;
    void setText(const QString& str);

    QList<QPair<int, int> > getAdjacentNodes() const;

    friend bool operator== (GraphNode::const_reference first, GraphNode::const_reference second);
    friend bool operator!= (GraphNode::const_reference first, GraphNode::const_reference second);

private:
    void setIndex(int i);
    void addEdge(GraphEdge* edge);
    void removeEdge(GraphEdge* edge);

    int index;
    QString text;
    QLinkedList<GraphEdge*> edges;
};

bool operator== (GraphNode::const_reference first, GraphNode::const_reference second);
bool operator!= (GraphNode::const_reference first, GraphNode::const_reference second);
