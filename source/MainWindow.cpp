
#include "header/MainWindow.h"

void MainWindow::newActionSlot(){

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("UMLedit");

    //instantiate elements and set properties:

    menuBar = new MenuBar(this);

    //menuBar/fileMenu
    fileMenu = new QMenu(menuBar);
    fileMenu->setTitle(tr("File"));
    newAction = new QAction(fileMenu);
    newAction->setText(tr("New"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newActionSlot()));
    openAction = new QAction(fileMenu);
    openAction->setText(tr("Open"));
    exitAction = new QAction(fileMenu);
    exitAction->setText(tr("Exit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //menuBar/editMenu
    editMenu = new QMenu(menuBar);
    editMenu->setTitle(tr("Edit"));

    //drawer menu mode:
    tabWidget = new QTabWidget(this);


    menuButton = new QPushButton(tabWidget);
    tabWidget->addTab(menuButton, tr("Tab1"));

    //assign elements:

    //menuBar/fileMenu
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //menuBar/editMenu
    menuBar->addMenu(editMenu);

    //drawer menu mode:
    setCentralWidget(tabWidget);
    //tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);


    this->showMaximized();
}

MainWindow::~MainWindow(){

}
