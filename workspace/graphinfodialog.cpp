#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "graphinfodialog.h"
#include "graph/incidencematrix.h"
#include "algorithm/graphalgorithm.h"
#include "workspace.h"

using namespace GraphModel;


GraphInfoDialog::GraphInfoDialog(Graph& graph, QWidget* parent)
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
    QLabel* eulerianLabel = new QLabel(tr("Eulerian graph:"));
    QLabel* eulerianCheckResult = new QLabel;

    GraphAlgorithm::Arguments args;
    args.graph = &graph;

    if (graph.getType() == Graph::Mixed || graph.getType() == Graph::Empty)
        eulerianCheckResult->setText(tr("undefined"));
    else
    {
        EulerianGraphAlgorithm eulerianCheck;
        GraphAlgorithm::Result result = eulerianCheck.execute(args);

        eulerianCheckResult->setText(result.getBool() ? tr("yes") : tr("no"));
    }

    layout->addWidget(eulerianLabel, 4, 0);
    layout->addWidget(eulerianCheckResult, 4, 1);

    // graph radius
    GraphRadiusAlgorithm radiusAlgo;
    GraphAlgorithm::Result result = radiusAlgo.execute(args);

    QLabel* radiusLabel = new QLabel(tr("Graph's radius:"));
    QLineEdit* radiusEdit = new QLineEdit(QString::number(result.getInt()));
    radiusEdit->setReadOnly(true);
    radiusEdit->setAlignment(Qt::AlignCenter);
    layout->addWidget(radiusLabel, 5, 0);
    layout->addWidget(radiusEdit, 5, 1);

    // graph diameter
    GraphDiameterAlgorithm diameterAlgo;
    result = diameterAlgo.execute(args);

    QLabel* diameterLabel = new QLabel(tr("Graph's diameter:"));
    QLineEdit* diameterEdit = new QLineEdit(QString::number(result.getInt()));
    diameterEdit->setReadOnly(true);
    diameterEdit->setAlignment(Qt::AlignCenter);
    layout->addWidget(diameterLabel, 6, 0);
    layout->addWidget(diameterEdit, 6, 1);

    setLayout(layout);
}

void GraphInfoDialog::fillIncidenceMatrixTable()
{
    GraphModel::IncidenceMatrix matrix(graph);

    incidenceMatrixTable = new QTableWidget(matrix.getRowsCount(), matrix.getColumnsCount(), this);
    incidenceMatrixTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // fill table
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
