#pragma once

#include <QTimer>

#include "graphalgorithm.h"

class Workspace;


namespace GraphModel
{

class AlgorithmHandler : public QObject
{
    Q_OBJECT
public:
    AlgorithmHandler(Workspace* w);

    void handleAlgorithm(GraphAlgorithm *algo);
    void stopAlgorithm();

public slots:
    void removeHighlight();

private slots:
    void highlightElement();    

private:
    Workspace* workspace;
    GraphAlgorithm* algorithm;

    QTimer* timer;

    QString highlightPenColor = "green";
    QString highlightBrushColor = "light green";
};

}
