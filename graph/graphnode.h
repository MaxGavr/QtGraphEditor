#pragma once

#include <QString>
#include <QList>
#include <QLinkedList>
#include <QtAlgorithms>

#include "graphedge.h"



class GraphNode
{
public:
    typedef const GraphNode& const_reference;

    GraphNode(int i);
    GraphNode(int i, const QString& str);
    ~GraphNode();

    int getIndex() const;

    QString getText() const;
    void setText(const QString& str);

    void addEdge(GraphEdge* edge);
    void removeEdge(GraphEdge* edge);

    QList<int> getAdjacentNodes() const;

    friend bool operator== (GraphNode::const_reference first, GraphNode::const_reference second);
    friend bool operator!= (GraphNode::const_reference first, GraphNode::const_reference second);

private:
    const int index;
    QString text;
    QLinkedList<GraphEdge*> edges;
};

bool operator== (GraphNode::const_reference first, GraphNode::const_reference second);
bool operator!= (GraphNode::const_reference first, GraphNode::const_reference second);
