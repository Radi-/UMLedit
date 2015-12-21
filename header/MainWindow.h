#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QTabWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QListWidget>
#include <QVector2D>
#include <QUndoView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "qttreepropertybrowser.h"
#include "header/Object.h"
#include "header/Connector.h"

class MainWindow : public QMainWindow
{

Q_OBJECT

private slots:

    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();
    void undoActionSlot();
    void redoActionSlot();
    void cutActionSlot();
    void copyActionSlot();
    void pasteActionSlot();


private:

    QStatusBar* statusBar;

    QToolBar* fileToolBar;
    QToolBar* editToolBar;

    QMenuBar* menuBar;
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* burgerMenu;

    QAction* newAction;
    QAction* openAction;
    QAction* exitAction;
    QAction* saveAction;
    QAction* undoAction;
    QAction* redoAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;

    QTabWidget* tabWidget;
    QPushButton* menuButton;

    QDockWidget* objectWindow;
    QDockWidget* connectorWindow;
    QDockWidget* propertyWindow;
    QDockWidget* historyWindow;

    QListWidget* objectList;
    QListWidget* connectorList;
    QUndoView* historyView;
    QtTreePropertyBrowser* propertyBrowser;

    QVector2D menuButtonSize;

    //QGraphicsScene *graphicsScene;


public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
