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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

void MainWindow::createMenuActions()
{
    newFileAction = new QAction(tr("&New file"), this);
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create new file"));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openFileAction = new QAction(tr("&Open file"), this);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open existing file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(open()));

    saveFileAction = new QAction(tr("&Save file"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save current file"));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsFileAction = new QAction(tr("&Save file as"), this);
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

    selectNode = new QAction(tr("Select element"), editActionGroup);
    selectNode->setShortcut(Qt::Key_1);
    selectNode->setCheckable(true);
    selectNode->setStatusTip(tr("Select existing graph elements"));
    connect(selectNode, SIGNAL(toggled(bool)), workingArea, SLOT(toggleSelectionMode(bool)));

    createNode = new QAction(tr("Create node"), editActionGroup);
    createNode->setShortcut(Qt::Key_2);
    createNode->setStatusTip(tr("Create new graph vertex"));
    createNode->setCheckable(true);
    connect(createNode, SIGNAL(toggled(bool)), workingArea, SLOT(toggleNodeCreationMode(bool)));

    createEdge = new QAction(tr("Create edge"), editActionGroup);
    createEdge->setShortcut(Qt::Key_3);
    createEdge->setStatusTip(tr("Create a connection between two selected nodes"));
    createEdge->setCheckable(true);
    connect(createEdge, SIGNAL(toggled(bool)), workingArea, SLOT(toggleEdgeCreationMode(bool)));

    deleteElement = new QAction(tr("Delete element"), editActionGroup);
    deleteElement->setShortcut(Qt::Key_4);
    deleteElement->setStatusTip(tr("Delete graph node or edge"));
    deleteElement->setCheckable(true);
    connect(deleteElement, SIGNAL(toggled(bool)), workingArea, SLOT(toggleDeletionMode(bool)));

    selectNode->trigger();
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
    fileToolBar->addAction(newFileAction);
    fileToolBar->addAction(openFileAction);
    fileToolBar->addAction(saveFileAction);

    editToolBar = new QToolBar(tr("&Edit"));
    addToolBar(Qt::LeftToolBarArea, editToolBar);
    editToolBar->addActions(editActionGroup->actions());
}

void MainWindow::newFile()
{
    if (saveConfirmation())
    {
        // TO DO: creating new graph file
    }
}

bool MainWindow::saveConfirmation()
{
    // TO DO: ignore confirmation if graph has not been modified
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
    if (saveConfirmation()) // save current file before opening another one
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open graph"), ".",
                                                        tr("Graph files (*.gph)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    if (saveConfirmation())
    {
        // TO DO: loading existing graph file
    }
    return true;
}

bool MainWindow::save()
{
    workingArea->saveGraphToFile();
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    return true;
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save graph as"), ".",
                                                    tr("Graph files (*.gph)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (saveConfirmation())
    {
        // TO DO: saving settings
    }
    else
    {
        event->ignore();
    }
}
