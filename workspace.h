#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QPair>
#include <QHBoxLayout>

#include "mainwindow.h"

class Node;
class Edge;

class Workspace : public QGraphicsView
{
    Q_OBJECT
public:
    typedef QPair<Node *, Node *> NodePair;

    Workspace(MainWindow* parent);

    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);

    void createNode(const QPoint& pos);
    void createEdge(const NodePair);

    //Edge* getSelectedEdge();
    //Node* getSelectedNode();
    NodePair getSelectedNodePair();

private slots:
    void createEdge();
    void toggleNodeCreationMode(bool isToggled);
    void toggleEdgeCreationMode(bool isToggled);

private:
    const int WIDTH = 640;
    const int HEIGHT = 480;

    NodePair selectedNodes;

    bool nodeCreationMode;
    bool edgeCreationMode;
    //bool firstNodeSelected;
};
