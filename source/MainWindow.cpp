
#include <QBoxLayout>
#include <QDebug>

#include "header/MainWindow.h"

void MainWindow::newActionSlot(){

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


    //drawer menu mode:
    tabWidget = new QTabWidget(this);
    tabWidget->setTabBarAutoHide(false);
    tabWidget->setTabsClosable(true);

    QWidget* randWidget = new QWidget();
    menuButton = new QPushButton(tabWidget);
    menuButton->setText(tr("Menu"));
    tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);
    tabWidget->addTab(randWidget, tr("Tab1"));
    int height = tabWidget->cornerWidget(Qt::TopLeftCorner)->height();
    tabWidget->cornerWidget(Qt::TopLeftCorner)->setMinimumHeight(height);
    tabWidget->setMinimumHeight(height);
    tabWidget->tabBar()->setMinimumHeight(height);
    tabWidget->removeTab(0);
    tabWidget->setVisible(true);
    menuButton->setVisible(true);
    tabWidget->tabBar()->setVisible(true);


    //dockable windows:
    objectWindow = new QDockWidget(this);
    connectorWindow = new QDockWidget(this);
    propertyWindow = new QDockWidget(this);
    historyWindow = new QDockWidget(this);

    objectList = new QTreeWidget(objectWindow);
    objectWindow->setWidget(objectList);
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
