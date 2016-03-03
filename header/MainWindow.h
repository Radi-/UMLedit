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
#include <QPointer>

#include "qttreepropertybrowser.h"
#include "header/CommentObject.h"
#include "header/ClassObject.h"
#include "header/Connector.h"
#include "header/GraphicsView.h"
#include "header/SettingsWindow.h"

class MainWindow : public QMainWindow
{

Q_OBJECT

private slots:

    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent* event);

    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();
    void saveAsActionSlot();
    void undoActionSlot();
    void redoActionSlot();
    void cutActionSlot();
    void copyActionSlot();
    void pasteActionSlot();
    void settingsActionSlot();
    void showObjectDockActionSlot(bool checked);
    void showConnectorDockActionSlot(bool checked);
    void showHistoryDockActionSlot(bool checked);
    void showPropertyDockActionSlot(bool checked);

    bool tabCloseRequestedSlot(int index);
    void tabBarDoubleClicked(int index);

    void setPropertyBrowser();

    void connectorListItemSelectionChanged();
    void connectorListTabletModeItemSelectionChanged();
    void objectListItemSelectionChanged();
    void objectListTabletModeItemSelectionChanged();
    void updateElementPlacementGhostPosition(qreal x, qreal y);
    void placeElement(Qt::MouseButton mouseButton);
    void updateTabletModeTabWidget(Qt::Key key);

    void objectWindowVisibilityChanged(bool visibility);
    void connectorWindowVisibilityChanged(bool visibility);
    void propertyWindowVisibilityChanged(bool visibility);
    void historyWindowVisibilityChanged(bool visibility);

private:

    enum class ElementPlacementStatus{
        none,
        object,
        connectorStartPoint,
        connectorEndPoint
    };

    bool tabletModeEnabled;
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
    QMenu* contextMenu;

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

    QPointer<QTabWidget> tabWidget;
    QPushButton* menuButton;

    QDockWidget* objectWindow;
    QDockWidget* connectorWindow;
    QPointer<QDockWidget> propertyWindow;
    QDockWidget* historyWindow;

    QListWidget* objectList;   
    QListWidget* connectorList;

    QListWidget* objectListTabletMode;
    QListWidget* connectorListTabletMode;
    QTabWidget* tabletModeTabWidget;

    QUndoView* historyView;
    QtTreePropertyBrowser* propertyBrowser;

    SettingsWindow* settings;
    ElementPlacementStatus elementPlacementStatus;

    enum ElementType{
        classObject,
        commentObject,
        association,
        aggregation,
        composition,
        generalization,
        realization,
        dependency
    };

    Element* elementPlacementGhost;

    void connectSignals();
    void createMenus();
    void createToolBars();
    void createActions();
    void createDockWidgets();
    void initTabWidget();
    void createTabletModeWidgets();

    void setListUnselected(QListWidget* list);
    void setElementPlacementStatus(ElementPlacementStatus elementPlacementStatus);

public slots:
    void updateStatusBarCoordinates(qreal x, qreal y);
    void setDrawingTabletModeOn(bool enabled);

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
