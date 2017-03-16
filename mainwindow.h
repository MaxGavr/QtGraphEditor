#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QCloseEvent>

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
    //void openRecentFile();

private:
    // initializing functions
    void createMenuActions();
    void createEditActions();
    void createMenus();
    void createToolBars();

    bool saveConfirmation();

    bool saveFile(const QString& fileName);
    bool loadFile(const QString& fileName);

    void setCurrentFile(const QString& fileName);

    /*QStringList recentFiles;
    QString currentFile;
    const int MaxRecentFiles = 5;
    QAction* recentFilesOpenActions[MaxRecentFiles];*/

    // menus and toolbars
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;
    QToolBar* fileToolBar;
    QToolBar* editToolBar;

    // menu and toolbar actions
    QAction* newFileAction;
    QAction* openFileAction;
    QAction* saveFileAction;
    QAction* saveAsFileAction;
    QAction* exitAction;
    QAction* aboutQtAction;

    // graph editing actions
    QAction* createNode;
    QAction* createEdge;

    // central widget, where graphs will be drawn
    Workspace* workingArea;
};
