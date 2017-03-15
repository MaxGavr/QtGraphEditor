#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QPair>
#include <QHBoxLayout>

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

    void createNode(const QPointF& pos);

    //Edge* getSelectedEdge();
    //Node* getSelectedNode();
    NodePair getSelectedNodePair();

private slots:
    void createEdge();

private:
    QGraphicsScene* scene;
    QGraphicsView* view;

    const int WIDTH = 640;
    const int HEIGHT = 480;
};
