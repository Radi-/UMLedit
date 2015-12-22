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
#include <QUndoView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "qttreepropertybrowser.h"
#include "header/CommentObject.h"
#include "header/ClassObject.h"
#include "header/Connector.h"
#include "header/GraphicsView.h"

class MainWindow : public QMainWindow
{

Q_OBJECT

private slots:

    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();
    void saveAsActionSlot();
    void undoActionSlot();
    void redoActionSlot();
    void cutActionSlot();
    void copyActionSlot();
    void pasteActionSlot();

    bool tabCloseRequestedSlot(int index);


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
    QAction* saveAsAction;
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

    void connectSignals();


public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
