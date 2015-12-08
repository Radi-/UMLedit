
#include <QBoxLayout>

#include "header/MainWindow.h"

void MainWindow::newActionSlot(){

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("UMLedit");

    QWidget* window = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(window);
    menuBar = new MenuBar(window);
    //instantiate elements and set properties:

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

    QWidget* randWidget = new QWidget();
    menuButton = new QPushButton(tabWidget);
    menuButton->setText(tr("Menu"));
    tabWidget->addTab(randWidget, tr("Tab1"));

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
    layout->setMenuBar(menuBar);
    layout->addWidget(tabWidget);
    window->setLayout(layout);
    setCentralWidget(window);
    tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);


    this->showMaximized();
}

MainWindow::~MainWindow(){

}
