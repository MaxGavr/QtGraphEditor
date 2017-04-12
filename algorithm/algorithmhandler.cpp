#include "algorithmhandler.h"
#include "workspace/workspace.h"

AlgorithmHandler::AlgorithmHandler(Workspace *w)
{
    workspace = w;
    timer = NULL;
    algorithm = NULL;
}

void AlgorithmHandler::handleAlgorithm(GraphAlgorithm* algo)
{
    algorithm = algo;

    algorithm->execute(*workspace->graph);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(highlightElement()));
    timer->start(1000);
}

void AlgorithmHandler::highlightElement()
{
    if (!algorithm->emptySequence())
    {
        GraphAlgorithm::GraphElement element = algorithm->getNextElement();
        if (element.first != -1)
        {
            GraphicsNodeItem* nodeItem;
            nodeItem = workspace->findNodeItem(workspace->graph->retrieveNode(element.first));
            QPen pen = nodeItem->pen();
            pen.setColor(highlightPenColor);
            nodeItem->setBrush(QBrush(QColor(highlightBrushColor)));
            nodeItem->setPen(pen);
        }
        else
        {
            GraphicsEdgeItem* edgeItem;
            edgeItem = workspace->findEdgeItem(workspace->graph->retrieveEdge(element.second));
            QPen pen = edgeItem->pen();
            pen.setColor(highlightPenColor);
            edgeItem->setPen(pen);
        }
    }
    else
        timer->stop();
}



