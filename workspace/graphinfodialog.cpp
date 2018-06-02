#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>

#include "graphinfodialog.h"
#include "graph/incidencematrix.h"
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

    QLabel* matrixLabel = new QLabel(tr("Incidence matrix:"));
    layout->addWidget(matrixLabel, 0, 0);
    layout->addWidget(incidenceMatrixTable, 1, 0);

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
