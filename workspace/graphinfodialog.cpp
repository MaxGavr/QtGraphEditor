#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "graphinfodialog.h"
#include "graph/incidencematrix.h"
#include "algorithm/graphalgorithm.h"
#include "workspace.h"


GraphInfoDialog::GraphInfoDialog(const GraphModel::Graph& graph, QWidget* parent)
    : QDialog(parent), graph(graph)
{
    fillIncidenceMatrixTable();

    manageLayout();
}

GraphInfoDialog::~GraphInfoDialog()
{
}

void GraphInfoDialog::manageLayout()
{
    QGridLayout* layout = new QGridLayout();

    // nodes count
    QLabel* nodesLabel = new QLabel(tr("Nodes:"));
    QLineEdit* nodesCount = new QLineEdit(QString::number(graph.countNodes()));
    nodesCount->setReadOnly(true);
    nodesCount->setAlignment(Qt::AlignCenter);
    layout->addWidget(nodesLabel, 0, 0);
    layout->addWidget(nodesCount, 0, 1);

    // edges count
    QLabel* edgesLabel = new QLabel(tr("Edges:"));
    QLineEdit* edgesCount = new QLineEdit(QString::number(graph.countEdges()));
    edgesCount->setReadOnly(true);
    edgesCount->setAlignment(Qt::AlignCenter);
    layout->addWidget(edgesLabel, 1, 0);
    layout->addWidget(edgesCount, 1, 1);

    // incidence matrix
    QLabel* matrixLabel = new QLabel(tr("Incidence matrix:"));
    layout->addWidget(matrixLabel, 2, 0, 1, 2);
    layout->addWidget(incidenceMatrixTable, 3, 0, 1, 2);

    // check for eulerian graph
    GraphModel::EulerianGraphAlgorithm eulerianCheck;
    eulerianCheck.execute(graph);

    QLabel* eulerianLabel = new QLabel(tr("Eulerian graph:"));
    QLabel* eulerianCheckResult = new QLabel(eulerianCheck.isEulerian() ? tr("yes") : tr("no"));
    layout->addWidget(eulerianLabel, 4, 0);
    layout->addWidget(eulerianCheckResult, 4, 1);

    setLayout(layout);
}

void GraphInfoDialog::fillIncidenceMatrixTable()
{
    GraphModel::IncidenceMatrix matrix(graph);

    incidenceMatrixTable = new QTableWidget(matrix.getRowsCount(), matrix.getColumnsCount(), this);
    incidenceMatrixTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int row = 0; row < matrix.getRowsCount(); ++row)
    {
        for (int column = 0; column < matrix.getColumnsCount(); ++column)
        {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix.getAt(column, row)));
            item->setTextAlignment(Qt::AlignCenter);
            incidenceMatrixTable->setItem(row, column, item);
        }
    }

    // set column labels (edge identifiers)
    QStringList horizontalLabels;
    for (int column = 0; column < matrix.getColumnsCount(); ++column)
        horizontalLabels.push_back(matrix.getEdgeIdentifier(column));
    incidenceMatrixTable->setHorizontalHeaderLabels(horizontalLabels);

    // set row labels (node identifiers)
    QStringList verticalLabels;
    for (int row = 0; row < matrix.getRowsCount(); ++row)
        verticalLabels.push_back(matrix.getNodeIdentifier(row));
    incidenceMatrixTable->setVerticalHeaderLabels(verticalLabels);
}
