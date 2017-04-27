#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QPair>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QXmlStreamWriter>
#include <QTimer>

#include <algorithm>
#include <functional>

#include "workspace/mainwindow.h"
#include "algorithm/algorithmhandler.h"
#include "graphics/graphicsedgeitem.h"

class Workspace : public QGraphicsView
{
    Q_OBJECT
public:
    friend class AlgorithmHandler;

    using NodePair = QPair<GraphicsNodeItem *, GraphicsNodeItem *>;

    enum { defaultMode = 0, nodeCreationMode = 1, edgeCreationMode = 2, deletionMode = 3 };

    Workspace(QWidget* parent = 0);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent* event);

    void manageEdgeCreation(const QPoint& location);

    void setElementContent(QGraphicsItem *item);

    void createNode(const QPoint& pos, const QString &idtf = "");
    void deleteElementAtPosition(const QPoint& pos);
    void deleteElement(QGraphicsItem* item);
    void deleteSelectedElements();

    GraphicsNodeItem* findNodeItem(GraphNode::const_ref graphNode);
    GraphicsEdgeItem* findEdgeItem(GraphEdge::const_ref graphEdge);

    void clearSelection();

    void toggleMode(int mode, bool toggled);

    bool saveGraphToFile(const QString &saveFileName);
    bool loadGraphFromFile(const QString &loadFileName);

    void deleteGraph();

private slots:
    void createEdge(GraphicsNodeItem *firstNode, GraphicsNodeItem *secondNode, int weight = 0);
    void createEdge(int firstNodeIndex, int secondNodeIndex, int weight = 0);

    void toggleSelectionMode(bool isToggled);
    void toggleNodeCreationMode(bool isToggled);
    void toggleEdgeCreationMode(bool isToggled);
    void toggleDeletionMode(bool isToggled);

    void runAlgorithm();
    void resetElementsView();

private:
    GraphicsNodeItem* getTopmostNodeItem(QList<QGraphicsItem*> items);
    QGraphicsItem* getSelectedItem();
    QList<GraphicsNodeItem *> getNodes() const;
    QList<GraphicsEdgeItem *> getEdges() const;

    void clearDrawingLine();

    std::function<GraphicsNodeItem *(QGraphicsItem *)> toNode;
    std::function<GraphicsEdgeItem *(QGraphicsItem *)> toEdge;

    const int WIDTH = 1024;
    const int HEIGHT = 768;

    Graph* graph;
    AlgorithmHandler* algoHandler;

    QGraphicsLineItem* drawingLine;
    NodePair selectedNodes;

    int toggledMode;
};
