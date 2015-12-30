
#include <QBoxLayout>
#include <QUndoView>
#include <QDebug>
#include <QFileDialog>
#include <QIcon>
#include <QListWidgetItem>
#include <QMessageBox>

#include "header/MainWindow.h"
#include "header/GraphicsScene.h"

void MainWindow::closeEvent(QCloseEvent *event){

    bool ignoreEvent = false;

    while(tabWidget->count() > 0){
        if(!this->tabCloseRequestedSlot(0)){
            ignoreEvent = true;
            break;
        }

    }

    if(ignoreEvent){
        event->ignore();
    }
    else{
        event->accept();
    }
}

void MainWindow::newActionSlot(){

    GraphicsView* view = new GraphicsView(this);
    view->setFrameStyle(QFrame::NoFrame);
    view->setMouseTracking(true);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    GraphicsScene* scene = new GraphicsScene(this);
    connect(scene, SIGNAL(cursorPositionChanged(qreal,qreal)), this, SLOT(updateStatusBarCoordinates(qreal,qreal)));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(setPropertyBrowser()));
    view->setScene(scene);
    tabWidget->addTab(view, tr("Project 1"));

    //temporary test:
    QGraphicsItem *item = new CommentObject(QPoint(100, 50), QColor(200, 200, 200, 255));
    item->setPos(QPointF(0, 0));
    scene->addItem(item);
    static_cast<CommentObject*>(item)->setColour(QColor(100, 0, 150, 200));

    item = new ClassObject(QPoint(200, 150), QColor(200, 200, 200, 255));
    item->setPos(QPointF(100, 100));
    scene->addItem(item);

    Connector* connector = new Connector();
    connector->setPos(QPoint(100,100));
    connector->setEndPoint(QPoint(-200, 200));
    connector->setType(Connector::Type::dependency);
    connector->setColour(Qt::black);
    scene->addItem(connector);

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
    //TBI in production version
}

void MainWindow::redoActionSlot(){
    //TBI in production version
}

void MainWindow::cutActionSlot(){
    //TBI in production version
}

void MainWindow::copyActionSlot(){
    //TBI in production version
}

void MainWindow::pasteActionSlot(){
    //TBI in production version
}

void MainWindow::connectSignals(){

    connect(newAction, SIGNAL(triggered()), this, SLOT(newActionSlot()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openActionSlot()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveActionSlot()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveActionSlot()));
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
    propertyWindow->setWidget(selectionLabel);
    tabWidget->removeTab(index);
    delete view;
    if(tabWidget->count() > 0){
        setPropertyBrowser();
    }
    return true;
}

void MainWindow::setPropertyBrowser(){
    QGraphicsView* view = static_cast<QGraphicsView*>(tabWidget->currentWidget());
    QGraphicsScene* scene = view->scene();
    if (scene->selectedItems().size() < 1){
        propertyWindow->setWidget(selectionLabel);
        selectionLabel->setText(tr("No item(s) selected."));
    }
    else if (scene->selectedItems().size() == 1){
        Element* item = static_cast<Element*>(scene->selectedItems().first());
        propertyWindow->setWidget(item->getPropertyBrowser());
    }
    else{
        propertyWindow->setWidget(selectionLabel);
        selectionLabel->setText(tr("Multiple items selected."));
    }
}

void MainWindow::updateStatusBarCoordinates(qreal x, qreal y){

    coordinatesLabel->setText(QString("(%1,%2)").arg(x).arg(y));
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("UMLedit");

    //instantiate elements and set properties:

    //statusBar
    statusBar = new QStatusBar(this);
    coordinatesLabel = new QLabel(statusBar);
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
    objectList->setFrameStyle(QFrame::NoFrame);
    objectList->addItem(new QListWidgetItem(QIcon(":/image/comm_object.svg"), tr("Comment"), objectList));
    objectList->addItem(new QListWidgetItem(QIcon(":/image/class_object.svg"), tr("Class"), objectList));
    objectWindow->setWidget(objectList);
    objectWindow->setContentsMargins(0,0,0,0);

    connectorList = new QListWidget(objectWindow);
    connectorList->setUniformItemSizes(true);
    connectorList->setViewMode(QListView::IconMode);
    connectorList->setFrameStyle(QFrame::NoFrame);
    connectorList->addItem(new QListWidgetItem(QIcon(":/image/assoc_arrow.svg"), tr("Arrow"), connectorList));
    connectorWindow->setWidget(connectorList);
    connectorWindow->setContentsMargins(0,0,0,0);

    historyView = new QUndoView(historyWindow);
    historyView->setFrameStyle(QFrame::NoFrame);
    historyWindow->setWidget(historyView);
    historyWindow->setContentsMargins(0,0,0,0);

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

    selectionLabel = new QLabel(propertyWindow);
    selectionLabel->setText(tr("No item(s) selected."));
    propertyWindow->setWidget(selectionLabel);
    //drawer menu mode:
    setMenuBar(menuBar);
    addToolBar(fileToolBar);
    addToolBar(editToolBar);
    setCentralWidget(tabWidget);
    tabWidget->setContentsMargins(0,0,0,0);
    connectSignals();
    this->showMaximized();

}

MainWindow::~MainWindow(){

}
