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

private:
    enum class ElementPlacementStatus{
        none,
        object,
        connectorStartPoint,
        connectorEndPoint
    };

private slots:

    void closeEvent(QCloseEvent *);

    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();
    void saveAsActionSlot();
    void undoActionSlot();
    void redoActionSlot();
    void cutActionSlot();
    void copyActionSlot();
    void pasteActionSlot();
    void showObjectDockActionSlot(bool checked);
    void showConnectorDockActionSlot(bool checked);
    void showHistoryDockActionSlot(bool checked);
    void showPropertyDockActionSlot(bool checked);

    bool tabCloseRequestedSlot(int index);

    void setPropertyBrowser();

    void connectorListItemSelectionChanged();
    void objectListItemSelectionChanged();
    void updateElementPlacementGhostPosition(qreal x, qreal y);

private:

    int newProjectCount;

    QLabel* selectionLabel;
    QLabel* coordinatesLabel;

    QStatusBar* statusBar;

    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QToolBar* viewToolBar;

    QMenuBar* menuBar;
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* toolsMenu;
    QMenu* viewMenu;
    QMenu* helpMenu;
    QMenu* burgerMenu;

    QAction* newAction;
    QAction* openAction;
    QAction* exitAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* exportAction;
    QAction* undoAction;
    QAction* redoAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* selectAllAction;
    QAction* selectNoneAction;
    QAction* settingsAction;
    QAction* arrangeGraphAction;
    QAction* zoomInAction;
    QAction* zoomOutAction;
    QAction* zoomResetAction;
    QAction* showObjectDockAction;
    QAction* showConnectorDockAction;
    QAction* showHistoryDockAction;
    QAction* showPropertyDockAction;
    QAction* showGridAction;
    QAction* gridSnapAction;
    QAction* helpContentsAction;
    QAction* aboutQtAction;
    QAction* aboutAction;

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

    ElementPlacementStatus elementPlacementStatus;

    enum QGraphicsItemType{
        classObject,
        commentObject,
        association,
        aggregation,
        composition,
        generalization,
        realization,
        dependency
    };

    QGraphicsItem* elementPlacementGhost;

    void connectSignals();
    void createMenus();
    void createToolBars();
    void createActions();
    void createDockWidgets();
    void initTabWidget();

    void setElementPlacementStatus(ElementPlacementStatus elementPlacementStatus);

public slots:
    void updateStatusBarCoordinates(qreal x, qreal y);

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
