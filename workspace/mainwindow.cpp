#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>

#include "workspace.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    workingArea = new QTabWidget(this);
    newFile();
    setCentralWidget(workingArea);
    connect(workingArea, SIGNAL(currentChanged(int)), this, SLOT(connectToolsToCurrentWidget()));

    QStatusBar* statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    createMenuActions();
    createEditActions();
    createMenus();
    createToolBars();

    connectToolsToCurrentWidget();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenuActions()
{
    newFileAction = new QAction(QIcon(":/icons/icon_new_file.png"), tr("&New file"), this);
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create new file"));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openFileAction = new QAction(QIcon(":/icons/icon_open_file.png"), tr("&Open file"), this);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open existing file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(open()));

    saveFileAction = new QAction(QIcon(":/icons/icon_save_file.png"), tr("&Save file"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save current file"));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsFileAction = new QAction(QIcon(":/icons/icon_save_as.png"), tr("&Save file as"), this);
    saveAsFileAction->setShortcut(QKeySequence::SaveAs);
    saveAsFileAction->setStatusTip(tr("Save current file in a certain way"));
    connect(saveAsFileAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    closeTabAction = new QAction(QIcon(":/icons/icon_close_tab.png"), tr("&Close tab"), this);
    closeTabAction->setShortcut(QKeySequence::Close);
    closeTabAction->setStatusTip(tr("Close current tab"));
    connect(closeTabAction, SIGNAL(triggered()), this, SLOT(closeTab()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show information about Qt library"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createEditActions()
{
    editActionGroup = new QActionGroup(this);

    selectNode = new QAction(QIcon(":/icons/icon_selection.png"), tr("Select element"), editActionGroup);
    selectNode->setShortcut(Qt::Key_1);
    selectNode->setCheckable(true);
    selectNode->setStatusTip(tr("Select existing graph elements"));

    createNode = new QAction(QIcon(":/icons/icon_node.png"), tr("Create node"), editActionGroup);
    createNode->setShortcut(Qt::Key_2);
    createNode->setStatusTip(tr("Create new graph vertex"));
    createNode->setCheckable(true);

    createEdge = new QAction(QIcon(":/icons/icon_edge.png"), tr("Create edge"), editActionGroup);
    createEdge->setShortcut(Qt::Key_3);
    createEdge->setStatusTip(tr("Create an undirected connection between two selected nodes"));
    createEdge->setCheckable(true);

    createArc = new QAction(QIcon(":/icons/icon_arc.png"), tr("Create arc"), editActionGroup);
    createArc->setShortcut(Qt::Key_4);
    createArc->setStatusTip(tr("Create a directed connection between two selected nodes"));
    createArc->setCheckable(true);

    deleteElement = new QAction(QIcon(":/icons/icon_trash.png"), tr("Delete element"), editActionGroup);
    deleteElement->setShortcut(Qt::Key_5);
    deleteElement->setStatusTip(tr("Delete graph node or edge"));
    deleteElement->setCheckable(true);

    runAlgorithm = new QAction(QIcon(":/icons/icon_algo.png"), tr("Find Hamiltonian cycle"), this);
    runAlgorithm->setShortcut(QKeySequence("Ctrl+R"));
    runAlgorithm->setStatusTip(tr("Find Hamiltonian cycle of current graph"));

    resetElements = new QAction(QIcon(":/icons/icon_refresh.png"), tr("Reset appearance"), this);
    resetElements->setShortcut(QKeySequence("Ctrl+A"));
    resetElements->setStatusTip(tr("Reset every element appearance"));

    showGraphInfo = new QAction(QIcon(":/icons/icon_info.png"), tr("Show graph info"), this);
    showGraphInfo->setShortcut(QKeySequence("Ctrl+I"));
    showGraphInfo->setStatusTip(tr("Show various properties of the current graph"));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsFileAction);

    fileMenu->addSeparator();
    fileMenu->addAction(closeTabAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addActions(editActionGroup->actions());

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->setIconSize(QSize(30, 30));
    fileToolBar->addAction(newFileAction);
    fileToolBar->addAction(openFileAction);
    fileToolBar->addAction(saveFileAction);
    fileToolBar->addAction(saveAsFileAction);
    fileToolBar->addAction(closeTabAction);

    editToolBar = new QToolBar(tr("&Edit"));
    editToolBar->setIconSize(QSize(30, 30));
    addToolBar(Qt::LeftToolBarArea, editToolBar);
    editToolBar->addActions(editActionGroup->actions());
    editToolBar->addAction(runAlgorithm);
    editToolBar->addAction(resetElements);
    editToolBar->addAction(showGraphInfo);
}

void MainWindow::newFile()
{
    int index = workingArea->addTab(new Workspace(), QString());
    workingArea->setTabText(index, QString("Graph №%1").arg(index + 1));
    workingArea->setCurrentIndex(index);
}

bool MainWindow::saveConfirmation()
{
    QString currentTabTitle = workingArea->tabText(workingArea->indexOf(getCurrentWorkspace()));
    QString warning = QString("%1 has been modified.\n Do you want to save changes?")
                              .arg(currentTabTitle);
    int respond = QMessageBox::warning(this, tr("Saving"), warning,
                                       QMessageBox::Yes | QMessageBox::No |
                                       QMessageBox::Cancel);
    if (respond == QMessageBox::Yes)
        return save();
    else if (respond == QMessageBox::Cancel)
        return false;
    return true;
}

void MainWindow::open()
{
    if (saveConfirmation())
    {
        QString loadFileName = QFileDialog::getOpenFileName(this,
                                                            tr("Loading existing graph"),
                                                            "",
                                                            tr("Graph (*.gph)"));
        if (!loadFileName.isEmpty())
        {
            getCurrentWorkspace()->loadGraphFromFile(loadFileName);
            currentFile = loadFileName;
        }
    }
}

bool MainWindow::save()
{
    if (currentFile.isEmpty())
        return saveAs();
    else
        return getCurrentWorkspace()->saveGraphToFile(currentFile);
}

bool MainWindow::saveAs()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save current graph"),
                                                        "new_graph.gph",
                                                        tr("Graph (*.gph)"));
    if (!saveFileName.isEmpty())
    {
        currentFile = saveFileName;
        return getCurrentWorkspace()->saveGraphToFile(saveFileName);
    }
    else
        return false;
}

void MainWindow::closeTab()
{
    if (saveConfirmation())
    {
        Workspace *workspace = getCurrentWorkspace();
        workingArea->removeTab(workingArea->indexOf(workspace));
        workspace->close();
    }
}

void MainWindow::connectToolsToCurrentWidget()
{
    Workspace *workspace = getCurrentWorkspace();

    connect(selectNode, SIGNAL(toggled(bool)), workspace, SLOT(toggleSelectionMode(bool)));
    connect(createNode, SIGNAL(toggled(bool)), workspace, SLOT(toggleNodeCreationMode(bool)));
    connect(createEdge, SIGNAL(toggled(bool)), workspace, SLOT(toggleEdgeCreationMode(bool)));
    connect(createArc, SIGNAL(toggled(bool)), workspace, SLOT(toggleArcCreationMode(bool)));
    connect(deleteElement, SIGNAL(toggled(bool)), workspace, SLOT(toggleDeletionMode(bool)));
    selectNode->toggle();

    connect(runAlgorithm, SIGNAL(triggered(bool)), workspace, SLOT(runAlgorithm()));
    connect(resetElements, SIGNAL(triggered(bool)), workspace, SLOT(resetElementsView()));
    connect(showGraphInfo, SIGNAL(triggered(bool)), workspace, SLOT(showGraphInfo()));
}

Workspace *MainWindow::getCurrentWorkspace()
{
    QWidget *currentWidget = workingArea->currentWidget();
    return static_cast<Workspace *>(currentWidget);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    for (int i = 0; i < workingArea->count(); i++)
    {
        workingArea->setCurrentIndex(i);
        if (!saveConfirmation())
            break;
    }
}
