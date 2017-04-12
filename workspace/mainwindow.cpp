#include "workspace.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    workingArea = new Workspace(this);
    setCentralWidget(workingArea);

    QStatusBar* statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    createMenuActions();
    createEditActions();
    createMenus();
    createToolBars();
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
    connect(selectNode, SIGNAL(toggled(bool)), workingArea, SLOT(toggleSelectionMode(bool)));

    createNode = new QAction(QIcon(":/icons/icon_node.png"), tr("Create node"), editActionGroup);
    createNode->setShortcut(Qt::Key_2);
    createNode->setStatusTip(tr("Create new graph vertex"));
    createNode->setCheckable(true);
    connect(createNode, SIGNAL(toggled(bool)), workingArea, SLOT(toggleNodeCreationMode(bool)));

    createEdge = new QAction(QIcon(":/icons/icon_edge.png"), tr("Create edge"), editActionGroup);
    createEdge->setShortcut(Qt::Key_3);
    createEdge->setStatusTip(tr("Create a connection between two selected nodes"));
    createEdge->setCheckable(true);
    connect(createEdge, SIGNAL(toggled(bool)), workingArea, SLOT(toggleEdgeCreationMode(bool)));

    deleteElement = new QAction(QIcon(":/icons/icon_trash.png"), tr("Delete element"), editActionGroup);
    deleteElement->setShortcut(Qt::Key_4);
    deleteElement->setStatusTip(tr("Delete graph node or edge"));
    deleteElement->setCheckable(true);
    connect(deleteElement, SIGNAL(toggled(bool)), workingArea, SLOT(toggleDeletionMode(bool)));

    selectNode->trigger();

    runAlgorithm = new QAction(QIcon(":/icons/icon_algo.png"), tr("Run Prim's algorithm"), this);
    runAlgorithm->setShortcut(QKeySequence("Ctrl+R"));
    runAlgorithm->setStatusTip(tr("Find minimum spanning tree for current graph"));
    connect(runAlgorithm, SIGNAL(triggered(bool)), workingArea, SLOT(runAlgorithm()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsFileAction);

    fileMenu->addSeparator();
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

    editToolBar = new QToolBar(tr("&Edit"));
    editToolBar->setIconSize(QSize(30, 30));
    addToolBar(Qt::LeftToolBarArea, editToolBar);
    editToolBar->addActions(editActionGroup->actions());
    editToolBar->addAction(runAlgorithm);
}

void MainWindow::newFile()
{
    if (saveConfirmation())
    {
        workingArea->deleteGraph();
        currentFile.clear();
    }
}

bool MainWindow::saveConfirmation()
{
    int respond = QMessageBox::warning(this, tr("Saving"),
                                       tr("Graph has been modified.\n"
                                          "Do you want to save changes?"),
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
            workingArea->loadGraphFromFile(loadFileName);
            currentFile = loadFileName;
        }
    }
}

bool MainWindow::save()
{
    if (currentFile.isEmpty())
        return saveAs();
    else
        return workingArea->saveGraphToFile(currentFile);
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
        return workingArea->saveGraphToFile(saveFileName);
    }
    else
        return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (saveConfirmation())
        ;
    else
        event->ignore();
}
