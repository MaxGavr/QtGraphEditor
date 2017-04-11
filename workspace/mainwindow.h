#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QCloseEvent>
#include <QStatusBar>

class Workspace;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();

private:
    void createMenuActions();
    void createEditActions();
    void createMenus();
    void createToolBars();

    bool saveConfirmation();

    QString currentFile;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;
    QToolBar* fileToolBar;
    QToolBar* editToolBar;

    QAction* newFileAction;
    QAction* openFileAction;
    QAction* saveFileAction;
    QAction* saveAsFileAction;
    QAction* exitAction;
    QAction* aboutQtAction;

    QActionGroup* editActionGroup;
    QAction* selectNode;
    QAction* createNode;
    QAction* createEdge;
    QAction* deleteElement;
    QAction* runAlgorithm;

    Workspace* workingArea;
};
