#pragma once

#include <QGraphicsLineItem>

class Node;

class Edge : public QGraphicsLineItem
{
public:
    Edge(Node* begin, Node* end);

    Node* getStartNode();
    Node* getEndNode();

    void trackNodes();

private:
    Node* startNode;
    Node* endNode;
};
