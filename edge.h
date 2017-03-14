#pragma once

#include <QGraphicsLineItem>
#include <QApplication>

class Node;

class Edge : public QGraphicsLineItem
{
    Q_DECLARE_TR_FUNCTIONS(Edge)
public:
    Edge(Node* begin, Node* end);

    Node* getStartNode();
    Node* getEndNode();

    void trackNodes();

private:
    Node* startNode;
    Node* endNode;
};
