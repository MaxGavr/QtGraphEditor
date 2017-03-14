#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QPair>

#include "mainwindow.h"

class Node;
class Edge;

class Workspace : public QWidget
{
    Q_OBJECT
public:
    typedef QPair<Node *, Node *> NodePair;

    Workspace(MainWindow* parent);

    void mouseDoubleClickEvent(QMouseEvent* event);

    void createNode(QPoint pos);

    //Edge* getSelectedEdge();
    //Node* getSelectedNode();
    NodePair getSelectedNodePair();

private slots:
    void createEdge();

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
};
