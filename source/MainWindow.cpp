
#include <QBoxLayout>
#include <QUndoView>
#include <QDebug>
#include <QFileDialog>
#include <QIcon>
#include <QListWidgetItem>
#include <QMessageBox>

#include "header/MainWindow.h"
#include "header/GraphicsView.h"


void MainWindow::newActionSlot(){

    GraphicsView* view = new GraphicsView(this);
    QGraphicsScene* scene = new QGraphicsScene();
    view->setScene(scene);
    tabWidget->addTab(view, tr("Project 1"));
    //temporary test:
    QGraphicsItem *item = new CommentObject(QPoint(100, 50), QColor(200, 200, 200, 255));
    item->setPos(QPointF(0, 0));
    scene->addItem(item);
    //static_cast<CommentObject*>(item)->setColour(QColor(100, 0, 150, 200));
    item = new ClassObject(QPoint(200, 150), QColor(200, 200, 200, 255));
    item->setPos(QPointF(200, 0));
    scene->addItem(item);
}

void MainWindow::openActionSlot(){
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Open File(s)"), QString(), tr("All Files (*.*);;"
                                                                                                 "UMLEdit File (*.uef)"));
    //To be implemented when the actual program is implemented
}

void MainWindow::saveActionSlot(){

    GraphicsView* view = (GraphicsView*)tabWidget->currentWidget();
    view->saveFile();
}

void MainWindow::saveAsActionSlot(){

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

void MainWindow::connectSignals(){

    connect(newAction, SIGNAL(triggered()), this, SLOT(newActionSlot()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openActionSlot()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveActionSlot()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undoActionSlot()));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redoActionSlot()));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cutActionSlot()));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyActionSlot()));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(pasteActionSlot()));

    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequestedSlot(int)));
}

bool MainWindow::tabCloseRequestedSlot(int index){
    GraphicsView* view = (GraphicsView*)tabWidget->widget(index);
    if (view->hasChanged()){
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  tr("Save document?"),
                                                                  tr("Do you want to save changes made to %1?")
                                                                  .arg(tabWidget->tabText(index)),
                                                                  QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(reply == QMessageBox::Yes){
            if (!view->saveFile()){
                return false;
            }
        }
        else if (reply == QMessageBox::Cancel){
            return false;
        }
    }
    delete view;
    return true;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("UMLedit");

    //instantiate elements and set properties:

    //statusBar
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

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
    openAction = new QAction(QIcon::fromTheme("document-open"), tr("Open"), fileMenu);
    saveAction = new QAction(QIcon::fromTheme("document-save"), tr("Save"), fileMenu);
    saveAsAction = new QAction(QIcon::fromTheme("document-save-as"), tr("Save As..."), fileMenu);
    exitAction = new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), fileMenu);

    //menuBar/editMenu
    undoAction = new QAction(QIcon::fromTheme("edit-undo"), tr("Undo"), editMenu);
    redoAction = new QAction(QIcon::fromTheme("edit-redo"), tr("Redo"), editMenu);
    cutAction = new QAction(QIcon::fromTheme("edit-cut"), tr("Cut"), editMenu);
    copyAction = new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), editMenu);
    pasteAction = new QAction(QIcon::fromTheme("edit-paste"), tr("Paste"), editMenu);

    //Create the tab widget which displays the projects:
    tabWidget = new QTabWidget(this);
    tabWidget->setTabBarAutoHide(false);
    tabWidget->setTabsClosable(true);

    //Menu button for the alternative mode when menubar is hidden
    menuButton = new QPushButton(tabWidget);
    //menuButton->setText(tr("Menu"));
    menuButton->setIcon(QIcon(":/image/menu_icon.svg"));
    tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);

    /*Horrible hack or, as some may say, a temporary workaround
    Basically set fixed height for menubutton by creating a temporary tab
    which is immediately deleted when the value is aquired */
    QWidget* randWidget = new QWidget();

    tabWidget->addTab(randWidget, tr("Temp"));

    menuButton->setFixedSize(48, menuButton->height()-1);
    menuButton->setFlat(true);

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


    objectList = new QListWidget(objectWindow);
    objectList->setUniformItemSizes(true);
    objectList->setGridSize(QSize(128, 128));
    objectList->setWordWrap(true);
    objectList->setViewMode(QListView::IconMode);
    objectList->addItem(new QListWidgetItem(QIcon(":/image/comm_object.svg"), tr("Comment"), objectList));
    objectList->addItem(new QListWidgetItem(QIcon(":/image/class_object.svg"), tr("Class"), objectList));
    objectWindow->setWidget(objectList);
    objectWindow->setContentsMargins(0,0,0,0);

    connectorList = new QListWidget(objectWindow);
    connectorList->setUniformItemSizes(true);
    connectorList->setViewMode(QListView::IconMode);
    connectorList->addItem(new QListWidgetItem(QIcon(":/image/assoc_arrow.svg"), tr("Arrow"), connectorList));
    connectorWindow->setWidget(connectorList);
    connectorWindow->setContentsMargins(0,0,0,0);

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
    fileMenu->addAction(saveAsAction);
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
    fileToolBar->addAction(saveAsAction);

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

    connectSignals();
    this->showMaximized();

}

MainWindow::~MainWindow(){

}
