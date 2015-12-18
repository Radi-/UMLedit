#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTabWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QTreeWidget>
#include <QVector2D>
#include <QUndoView>
#include <QGraphicsItem>
//#include <QGraphicsScene>

#include "qttreepropertybrowser.h"
#include "header/Object.h"
#include "header/Connector.h"

class MainWindow : public QMainWindow
{

Q_OBJECT

private slots:

    void newActionSlot();

private:

    QMenuBar* menuBar;
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* burgerMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* exitAction;

    QTabWidget* tabWidget;
    QPushButton* menuButton;

    QDockWidget* objectWindow;
    QDockWidget* connectorWindow;
    QDockWidget* propertyWindow;
    QDockWidget* historyWindow;

    QTreeWidget* objectList;
    QUndoView* historyView;
    QtTreePropertyBrowser* propertyBrowser;

    QVector2D menuButtonSize;

    //QGraphicsScene *graphicsScene;


public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
