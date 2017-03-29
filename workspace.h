#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QPair>
#include <QHBoxLayout>

#include <algorithm>
#include <functional>

#include "mainwindow.h"
#include "graph.h"

class GraphicsNodeItem;
class GraphicsEdgeItem;

class Workspace : public QGraphicsView
{
    Q_OBJECT
public:
    typedef QPair<GraphicsNodeItem *, GraphicsNodeItem *> NodePair;

    Workspace(MainWindow* parent);

    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);

    void createNode(const QPoint& pos);
    void deleteNode(GraphicsNodeItem* nodeItem);

    void deleteEdge(GraphicsEdgeItem* edgeItem);

    NodePair getSelectedNodePair();

private slots:
    void createEdge();
    void toggleNodeCreationMode(bool isToggled);
    void toggleEdgeCreationMode(bool isToggled);

private:
    const int WIDTH = 640;
    const int HEIGHT = 480;

    Graph* graph;

    NodePair selectedNodes;

    bool nodeCreationMode;
    bool edgeCreationMode;
};
