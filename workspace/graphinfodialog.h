#pragma once

#include <QDialog>

#include "graph/graph.h"

class Workspace;
class QTableWidget;


class GraphInfoDialog : public QDialog
{
    Q_OBJECT
public:
    GraphInfoDialog(const GraphModel::Graph& graph, QWidget* parent = 0);
    ~GraphInfoDialog();

private:
    void manageLayout();
    void fillIncidenceMatrixTable();

    const GraphModel::Graph& graph;

    QTableWidget* incidenceMatrixTable;
};
