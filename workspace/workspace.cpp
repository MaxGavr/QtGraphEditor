#include <QInputDialog>
#include <QXmlStreamWriter>
#include <QMouseEvent>

#include <algorithm>
#include <functional>

#include "workspace.h"
#include "graphinfodialog.h"

using namespace GraphModel;


Workspace::Workspace(QWidget* parent)
    : QGraphicsView(parent)
{
    QGraphicsScene* newScene = new QGraphicsScene(0, 0, WIDTH, HEIGHT);
    setScene(newScene);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setMaximumSize(QSize(WIDTH, HEIGHT));

    graph = new Graph();
    algoHandler = new AlgorithmHandler(this);
    drawingLine = NULL;

    toNode = [] (QGraphicsItem *item) {
        return qgraphicsitem_cast<GraphicsNodeItem *>(item);
    };
    toEdge = [] (QGraphicsItem *item) {
        return qgraphicsitem_cast<GraphicsEdgeItem *>(item);
    };
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    switch (toggledMode)
    {
        case defaultMode:
        {
            GraphicsNodeItem* node = toNode(scene()->itemAt(mapToScene(event->pos()), QTransform()));
            if (node)
                ensureVisible(node, 40, 40);
            break;
        }
        case edgeCreationMode:
        case arcCreationMode:
        {
            if (drawingLine)
            {
                drawingLine->setLine(QLineF(selectedNodes.first->getCenterPos(), mapToScene(event->pos())));
                ensureVisible(drawingLine);
            }
            break;
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Workspace::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (toggledMode == defaultMode)
        createNode(event->pos());
    else
        QGraphicsView::mouseDoubleClickEvent(event);
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    switch (toggledMode)
    {
        case defaultMode:
        {
            QGraphicsView::mousePressEvent(event);
            break;
        }
        case nodeCreationMode:
        {
            createNode(event->pos());
            break;
        }
        case edgeCreationMode:
        case arcCreationMode:
        {
            manageEdgeCreation(event->pos());
            break;
        }
        case deletionMode:
        {
            deleteElementAtPosition(event->pos());
            break;
        }
    }
}

void Workspace::keyPressEvent(QKeyEvent *event)
{
    clearDrawingLine();
    switch (event->key())
    {
        case Qt::Key_Delete:
        {
            deleteSelectedElements();
            break;
        }
        case Qt::Key_I:
        {
            setElementContent(getSelectedItem());
            break;
        }
        default:
        {
            clearDrawingLine();
            QWidget::keyPressEvent(event);
        }
    }
}

void Workspace::focusOutEvent(QFocusEvent *event)
{
    clearDrawingLine();
    QGraphicsView::focusOutEvent(event);
}

void Workspace::createNode(const QPoint& pos, const QString& idtf)
{
    Node::const_ref newGraphNode = graph->addNode(idtf);
    GraphicsNodeItem* newNodeItem = new GraphicsNodeItem(mapToScene(pos), newGraphNode);
    scene()->addItem(newNodeItem);
}

void Workspace::deleteElementAtPosition(const QPoint &pos)
{
    QGraphicsItem* item = scene()->itemAt(QPointF(mapToScene(pos)), QTransform());
    deleteElement(item);
}

void Workspace::deleteElement(QGraphicsItem *item)
{
    if (GraphicsNodeItem* node = toNode(item))
    {
        foreach (GraphicsEdgeItem* edge, node->getEdgeItems())
            deleteElement(edge);
        Node::const_ref graphNode = node->getGraphNode();
        delete node;
        graph->removeNode(graphNode);
    }
    else if (GraphicsEdgeItem* edge = toEdge(item))
    {
        Edge::const_ref graphEdge = edge->getGraphEdge();
        delete edge;
        graph->removeEdge(graphEdge);
    }
}

void Workspace::deleteSelectedElements()
{
    QList<QGraphicsItem *> items = scene()->selectedItems();
    std::partition(items.begin(), items.end(), toEdge);
    foreach (QGraphicsItem* item, items)
        deleteElement(item);
}

GraphicsNodeItem *Workspace::findNodeItem(Node::const_ref graphNode)
{
    QList<GraphicsNodeItem *> nodes = getNodes();
    foreach (GraphicsNodeItem *item, nodes)
    {
        if (item->getGraphNode() == graphNode)
            return item;
    }
    return NULL;
}

GraphicsEdgeItem *Workspace::findEdgeItem(Edge::const_ref graphEdge)
{
    QList<GraphicsEdgeItem *> edges = getEdges();
    foreach (GraphicsEdgeItem *edge, edges)
    {
        if (edge->getGraphEdge() == graphEdge)
            return edge;
    }
    return NULL;
}

void Workspace::manageEdgeCreation(const QPoint &location)
{
    GraphicsNodeItem* topmostNode = getTopmostNodeItem(scene()->items(QPointF(mapToScene(location))));
    if (topmostNode)
    {
        topmostNode->setSelected(true);
        if (!selectedNodes.first)
        {
            selectedNodes.first = topmostNode;
            drawingLine = scene()->addLine(QLine(location, location));
        }
        else if (selectedNodes.first && !selectedNodes.second)
        {
            selectedNodes.second = topmostNode;
            createEdge(selectedNodes.first, selectedNodes.second);
            clearDrawingLine();
            clearSelection();
        }
    }
    else
    {
        clearDrawingLine();
        clearSelection();
    }
}

void Workspace::setElementContent(QGraphicsItem* item)
{
    if (GraphicsNodeItem* node = toNode(item))
    {
        QString idtf = QInputDialog::getText(this,
                                             tr("Переименование узла"),
                                             tr("New file identifier:"),
                                             QLineEdit::Normal,
                                             node->getGraphNode().getText());
        graph->setNodeIdtf(node->getGraphNode(), idtf);
    }
    else if (GraphicsEdgeItem* edge = toEdge(item))
    {
        int weight = QInputDialog::getInt(this,
                                          tr("Changing edge weight"),
                                          tr("New weight:"));
        graph->setEdgeWeight(edge->getGraphEdge(), weight);
    }
}

void Workspace::createEdge(GraphicsNodeItem* firstNode, GraphicsNodeItem* secondNode, int weight)
{
    if (firstNode && secondNode)
    {
        try
        {
            bool isOriented = (toggledMode == arcCreationMode);
            Edge::const_ref newGraphEdge = graph->addEdge(firstNode->getGraphNode(),
                                                               secondNode->getGraphNode(),
                                                               weight,
                                                               isOriented);
            GraphicsEdgeItem* newEdge = new GraphicsEdgeItem(firstNode,
                                                             secondNode,
                                                             newGraphEdge);
            scene()->addItem(newEdge);
            clearSelection();
        }
        catch (const bad_graph_edge& e)
        {
            clearSelection();
            return;
        }
    }
}

void Workspace::createEdge(int firstNodeIndex, int secondNodeIndex, int weight)
{
    GraphicsNodeItem* firstNode = NULL;
    GraphicsNodeItem* secondNode = NULL;
    foreach (GraphicsNodeItem* node, getNodes())
    {
        if (node->getGraphNode().getIndex() == firstNodeIndex)
            firstNode = node;
        if (node->getGraphNode().getIndex() == secondNodeIndex)
            secondNode = node;
    }
    createEdge(firstNode, secondNode, weight);
}

void Workspace::toggleSelectionMode(bool isToggled)
{
    setMouseTracking(false);
    toggleMode(defaultMode, isToggled);
}

void Workspace::toggleMode(int mode, bool toggled)
{
    if (toggled)
    {
        toggledMode = mode;
        scene()->clearSelection();
    }
    else
        toggledMode = defaultMode;
}

bool Workspace::saveGraphToFile(const QString& saveFileName)
{
    QFile file(saveFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("graph");

    foreach (GraphicsNodeItem* node, getNodes()) {
        stream.writeStartElement("node");
        QXmlStreamAttributes attribs;
        attribs.append("x", QString::number(node->getCenterPos().x()));
        attribs.append("y", QString::number(node->getCenterPos().y()));
        attribs.append("index", QString::number(node->getGraphNode().getIndex()));
        attribs.append("content", node->getGraphNode().getText());
        stream.writeAttributes(attribs);
        stream.writeEndElement();
    }
    foreach (GraphicsEdgeItem *edge, getEdges())
    {
        stream.writeStartElement("edge");
        QXmlStreamAttributes attribs;
        attribs.append("begin", QString::number(edge->getGraphEdge().getIndex().first));
        attribs.append("end", QString::number(edge->getGraphEdge().getIndex().second));
        attribs.append("weight", QString::number(edge->getGraphEdge().getWeight()));
        stream.writeAttributes(attribs);
        stream.writeEndElement();
    }

    stream.writeEndElement();
    stream.writeEndDocument();
    file.close();
    return true;
}

bool Workspace::loadGraphFromFile(const QString& loadFileName)
{
    deleteGraph();

    QFile file(loadFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QXmlStreamReader stream(&file);

    while (!stream.atEnd() && !stream.hasError())
    {
        QXmlStreamReader::TokenType token = stream.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (stream.name() == "node")
            {
                QXmlStreamAttributes attribs = stream.attributes();

                QPoint pos(attribs.value("x").toInt(), attribs.value("y").toInt());
                QString text = attribs.value("content").toString();

                createNode(pos, text);
            }
            if (stream.name() == "edge")
            {
                QXmlStreamAttributes attribs = stream.attributes();

                int beginNodeIndex = attribs.value("begin").toInt();
                int endNodeIndex = attribs.value("end").toInt();
                int weight = attribs.value("weight").toInt();

                createEdge(beginNodeIndex, endNodeIndex, weight);
            }
        }
    }
    file.close();
    return true;
}

void Workspace::deleteGraph()
{
    algoHandler->stopAlgorithm();
    scene()->clear();
    delete drawingLine;
    delete graph;

    graph = new Graph();
}

void Workspace::toggleNodeCreationMode(bool isToggled)
{
    toggleMode(nodeCreationMode, isToggled);
}

void Workspace::toggleArcCreationMode(bool isToggled)
{
    setMouseTracking(true);
    toggleMode(arcCreationMode, isToggled);
}

void Workspace::toggleEdgeCreationMode(bool isToggled)
{
    setMouseTracking(true);
    toggleMode(edgeCreationMode, isToggled);
}

void Workspace::toggleDeletionMode(bool isToggled)
{
    deleteSelectedElements();
    toggleMode(deletionMode, isToggled);
}

void Workspace::runAlgorithm()
{
    HamiltonianCycleAlgorithm* algo = new HamiltonianCycleAlgorithm();
    algoHandler->handleAlgorithm(algo);
}

void Workspace::resetElementsView()
{
    algoHandler->removeHighlight();
}

void Workspace::showGraphInfo()
{
    GraphInfoDialog dlg(*graph, this);
    dlg.exec();
}

GraphicsNodeItem *Workspace::getTopmostNodeItem(QList<QGraphicsItem *> items)
{
    if (!items.isEmpty())
    {
        auto isNotNode = [this](QGraphicsItem* item) -> bool
                        { return !toNode(item); };
        items.erase(std::remove_if(items.begin(), items.end(), isNotNode), items.end());
        if (!items.isEmpty())
        {
            auto sortByZ = [](QGraphicsItem* firstItem, QGraphicsItem* secondItem)
                            { return firstItem->zValue() < secondItem->zValue(); };
            std::sort(items.begin(), items.end(), sortByZ);

            return toNode(items.first());
        }
    }
    return NULL;
}

QGraphicsItem* Workspace::getSelectedItem()
{
    QList<QGraphicsItem*> selectedItems = scene()->selectedItems();
    if (selectedItems.length() == 1)
        return selectedItems.first();
    else
        return NULL;
}

QList<GraphicsNodeItem *> Workspace::getNodes() const
{
    QList<QGraphicsItem *> items = scene()->items();
    QList<GraphicsNodeItem *> nodes;
    foreach (QGraphicsItem *item, items)
    {
        if (GraphicsNodeItem *node = toNode(item))
            nodes.append(node);
    }
    auto indexComp = [](GraphicsNodeItem* first, GraphicsNodeItem* second)
    {
        return first->getGraphNode().getIndex() < second->getGraphNode().getIndex();
    };

    std::sort(nodes.begin(), nodes.end(), indexComp);
    return nodes;
}

QList<GraphicsEdgeItem *> Workspace::getEdges() const
{
    QList<QGraphicsItem *> items = scene()->items();
    QList<GraphicsEdgeItem *> edges;
    foreach (QGraphicsItem *item, items)
    {
        if (GraphicsEdgeItem *edge = toEdge(item))
            edges.append(edge);
    }
    return edges;
}

void Workspace::clearDrawingLine()
{
    delete drawingLine;
    drawingLine = NULL;
}

void Workspace::clearSelection()
{
    scene()->clearSelection();
    selectedNodes = NodePair();
}
