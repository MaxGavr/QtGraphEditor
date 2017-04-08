#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QPair>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QXmlStreamWriter>

#include <algorithm>
#include <functional>

#include "workspace/mainwindow.h"
#include "graph/graph.h"

class GraphicsNodeItem;
class GraphicsEdgeItem;

class Workspace : public QGraphicsView
{
    Q_OBJECT
public:
    typedef QPair<GraphicsNodeItem *, GraphicsNodeItem *> NodePair;

    enum { defaultMode = 0, nodeCreationMode = 1, edgeCreationMode = 2, deletionMode = 3 };

    Workspace(MainWindow* parent);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);

    void manageEdgeCreation(const QPoint& location);

    void setElementContent(QGraphicsItem *item);

    void createNode(const QPoint& pos);
    void deleteElementAtPosition(const QPoint& pos);
    void deleteNode(GraphicsNodeItem* nodeItem);
    void deleteEdge(GraphicsEdgeItem* edgeItem);
    void deleteSelectedElements();

    NodePair getSelectedNodePair();
    void clearSelection();

    void toggleMode(int mode, bool toggled);

    void saveGraphToFile();

private slots:
    void createEdge();
    void toggleSelectionMode(bool isToggled);
    void toggleNodeCreationMode(bool isToggled);
    void toggleEdgeCreationMode(bool isToggled);
    void toggleDeletionMode(bool isToggled);

private:
    void deselectNodeItem(GraphicsNodeItem* nodeItem);
    GraphicsNodeItem* getTopmostNodeItem(QList<QGraphicsItem*> items);
    QGraphicsItem* getSelectedItem();

    QList<GraphicsNodeItem *> getNodes();
    QList<GraphicsEdgeItem *> getEdges();

    std::function<GraphicsNodeItem *(QGraphicsItem *)> toNode;
    std::function<GraphicsEdgeItem *(QGraphicsItem *)> toEdge;

    const int WIDTH = 1000;
    const int HEIGHT = 1000;

    Graph* graph;

    QGraphicsLineItem* drawingLine;
    NodePair selectedNodes;

    int toggledMode;
};
