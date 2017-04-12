#pragma once

#include <QTimer>

#include "graphalgorithm.h"

class Workspace;

class AlgorithmHandler : public QObject
{
    Q_OBJECT
public:
    AlgorithmHandler(Workspace* w);

    void handleAlgorithm(GraphAlgorithm *algo);

private slots:
    void highlightElement();

private:
    Workspace* workspace;
    GraphAlgorithm* algorithm;

    QTimer* timer;
};
