
#include <QBoxLayout>
#include <QUndoView>
#include <QDebug>

#include "header/MainWindow.h"


void MainWindow::newActionSlot(){

    //temporary test:
    /*QGraphicsItem *item = new Object();
    item->setPos(QPointF(23, 32));
    scene->addItem(item); */
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("UMLedit");

    //instantiate elements and set properties:

    //menuBar
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu(menuBar);
    fileMenu->setTitle(tr("File"));
    editMenu = new QMenu(menuBar);
    editMenu->setTitle(tr("Edit"));

    //menuBar/fileMenu
    newAction = new QAction(fileMenu);
    newAction->setText(tr("New"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newActionSlot()));
    openAction = new QAction(fileMenu);
    openAction->setText(tr("Open"));
    exitAction = new QAction(fileMenu);
    exitAction->setText(tr("Exit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //menuBar/editMenu


    //Create the tab widget which displays the projects:
    tabWidget = new QTabWidget(this);
    tabWidget->setTabBarAutoHide(false);
    tabWidget->setTabsClosable(true);

    //Menu button for the alternative mode when menubar is hidden
    menuButton = new QPushButton(this);
    menuButton->setText(tr("Menu"));
    tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);

    /*Horrible hack or, as some may say, a temporary workaround
    Basically set minimun width and height for tabbar and menubutton by
    creating a temporary tab which is immediately deleted when the values are aquired */
    QWidget* randWidget = new QWidget();

    tabWidget->addTab(randWidget, tr("Tab1"));

    menuButtonSize.setY(tabWidget->cornerWidget(Qt::TopLeftCorner)->height());
    menuButtonSize.setX(tabWidget->cornerWidget(Qt::TopLeftCorner)->width());

    tabWidget->cornerWidget(Qt::TopLeftCorner)->setMinimumHeight(menuButtonSize.y());
    tabWidget->cornerWidget(Qt::TopLeftCorner)->setMinimumWidth(menuButtonSize.x());
    tabWidget->tabBar()->setMinimumHeight(menuButtonSize.y());
    tabWidget->tabBar()->setMinimumWidth(menuButtonSize.x());

    tabWidget->removeTab(0);

    //dockable windows:
    objectWindow = new QDockWidget(this);
    connectorWindow = new QDockWidget(this);
    propertyWindow = new QDockWidget(this);
    historyWindow = new QDockWidget(this);

    objectWindow->setWindowTitle(tr("Objects"));
    connectorWindow->setWindowTitle(tr("Connectors"));
    propertyWindow->setWindowTitle(tr("Properties"));
    historyWindow->setWindowTitle(tr("History"));

    addDockWidget(Qt::RightDockWidgetArea, objectWindow);
    addDockWidget(Qt::RightDockWidgetArea, connectorWindow);
    addDockWidget(Qt::RightDockWidgetArea, historyWindow);
    addDockWidget(Qt::RightDockWidgetArea, propertyWindow);
    tabifyDockWidget(objectWindow, connectorWindow);


    objectList = new QTreeWidget(objectWindow);
    //objectList->
    objectWindow->setWidget(objectList);
    objectWindow->setContentsMargins(0,0,0,0);

    historyView = new QUndoView(historyWindow);
    historyWindow->setWidget(historyView);
    historyWindow->setContentsMargins(0,0,0,0);

    propertyBrowser = new QtTreePropertyBrowser(propertyWindow);
    propertyWindow->setWidget(propertyBrowser);
    propertyWindow->setContentsMargins(0,0,0,0);
    //assign elements:

    //menuBar/fileMenu
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //menuBar/editMenu
    menuBar->addMenu(editMenu);

    burgerMenu = new QMenu(this);
    burgerMenu->addMenu(fileMenu);
    burgerMenu->addMenu(editMenu);
    menuButton->setMenu(burgerMenu);

    //drawer menu mode:
    setMenuBar(menuBar);
    setCentralWidget(tabWidget);

    this->showMaximized();

}

MainWindow::~MainWindow(){

}
