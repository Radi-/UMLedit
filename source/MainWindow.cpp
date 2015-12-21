
#include <QBoxLayout>
#include <QUndoView>
#include <QDebug>
#include <QFileDialog>
#include <QIcon>

#include "header/MainWindow.h"


void MainWindow::newActionSlot(){

    QGraphicsView* view = new QGraphicsView();
    QGraphicsScene* scene = new QGraphicsScene();
    view->setScene(scene);
    tabWidget->addTab(view, tr("Project 1"));
    //temporary test:
    QGraphicsItem *item = new Object();
    item->setPos(QPointF(0, 0));
    static_cast<Object*>(item)->setColour(QColor(100, 0, 50, 255));
    scene->addItem(item);
}

void MainWindow::openActionSlot(){
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Open File(s)"), QString(), tr("All Files (*.*);;"
                                                                                                 "UMLEdit File (*.uef)"));
}

void MainWindow::saveActionSlot(){

}

void MainWindow::undoActionSlot(){

}

void MainWindow::redoActionSlot(){

}

void MainWindow::cutActionSlot(){

}

void MainWindow::copyActionSlot(){

}

void MainWindow::pasteActionSlot(){

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("UMLedit");

    //instantiate elements and set properties:

    //toolBar
    fileToolBar = new QToolBar(this);
    editToolBar = new QToolBar(this);

    //menuBar
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu(menuBar);
    fileMenu->setTitle(tr("File"));
    editMenu = new QMenu(menuBar);
    editMenu->setTitle(tr("Edit"));

    //menuBar/fileMenu
    newAction = new QAction(QIcon::fromTheme("document-new"), tr("New"), fileMenu);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newActionSlot()));
    openAction = new QAction(QIcon::fromTheme("document-open"), tr("Open"), fileMenu);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openActionSlot()));
    saveAction = new QAction(QIcon::fromTheme("document-save"), tr("Save"), fileMenu);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveActionSlot()));
    exitAction = new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), fileMenu);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //menuBar/editMenu
    undoAction = new QAction(QIcon::fromTheme("edit-undo"), tr("Undo"), editMenu);
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undoActionSlot()));
    redoAction = new QAction(QIcon::fromTheme("edit-redo"), tr("Redo"), editMenu);
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redoActionSlot()));
    cutAction = new QAction(QIcon::fromTheme("edit-cut"), tr("Cut"), editMenu);
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cutActionSlot()));
    copyAction = new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), editMenu);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyActionSlot()));
    pasteAction = new QAction(QIcon::fromTheme("edit-paste"), tr("Paste"), editMenu);
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(pasteActionSlot()));

    //Create the tab widget which displays the projects:
    tabWidget = new QTabWidget(this);
    tabWidget->setTabBarAutoHide(false);
    tabWidget->setTabsClosable(true);

    //Menu button for the alternative mode when menubar is hidden
    menuButton = new QPushButton(tabWidget);
    menuButton->setText(tr("Menu"));
    tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);

    /*Horrible hack or, as some may say, a temporary workaround
    Basically set minimun width and height for tabbar and menubutton by
    creating a temporary tab which is immediately deleted when the values are aquired */
    QWidget* randWidget = new QWidget();

    tabWidget->addTab(randWidget, tr("Temp"));

    menuButton->setMinimumHeight(menuButton->height()-1);
    menuButton->setMinimumWidth(menuButton->width()-20);
    menuButton->setMaximumHeight(menuButton->height());
    menuButton->setMaximumWidth(menuButton->width());

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
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //menuBar/editMenu
    menuBar->addMenu(editMenu);
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);

    burgerMenu = new QMenu(this);
    burgerMenu->addMenu(fileMenu);
    burgerMenu->addMenu(editMenu);
    menuButton->setMenu(burgerMenu);

    //drawer menu mode:
    setMenuBar(menuBar);
    addToolBar(fileToolBar);
    addToolBar(editToolBar);
    setCentralWidget(tabWidget);

    this->showMaximized();

}

MainWindow::~MainWindow(){

}
