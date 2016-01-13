
#include <QBoxLayout>
#include <QUndoView>
#include <QDebug>
#include <QFileDialog>
#include <QIcon>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QKeySequence>

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

    newProjectCount++;

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
    connect(scene, SIGNAL(cursorPositionChanged(qreal,qreal)), this, SLOT(updateElementPlacementGhostPosition(qreal,qreal)));
    view->setScene(scene);

    tabWidget->addTab(view, tr("Project %1").arg(newProjectCount));
    tabWidget->setCurrentIndex(tabWidget->count()-1);

    //temporary test:
    CommentObject* commentObject = new CommentObject(QPoint(100, 50), QColor(200, 200, 200, 255));
    commentObject->setPos(QPointF(0, 0));
    commentObject->setColour(QColor(100, 0, 150, 200));
    scene->addItem(commentObject);

    ClassObject* classObject = new ClassObject(QPoint(200, 150), QColor(200, 200, 200, 255));
    classObject->setPos(QPointF(100, 100));
    scene->addItem(classObject);

    Connector* connector = new Connector();
    connector->setPos(QPoint(100,100));
    connector->setEndPoint(QPoint(200, 200));
    connector->setType(Connector::Type::dependency);
    connector->setColour(Qt::black);  
    scene->addItem(connector);

    commentObject->connectConnectorStartPoint(Connection(connector, QPointF(0, 0)));
    classObject->connectConnectorEndPoint(Connection(connector, QPointF(0, 0)));

    if (!saveAction->isEnabled()) saveAction->setEnabled(true);
    if (!saveAsAction->isEnabled()) saveAsAction->setEnabled(true);
}

void MainWindow::openActionSlot(){
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Open File(s)"), QString(), tr("All Files (*.*);;"
                                                                                                 "UMLEdit File (*.uef)"));
    //To be implemented when the actual program is implemented
}

void MainWindow::saveActionSlot(){

    GraphicsView* view = static_cast<GraphicsView*>(tabWidget->currentWidget());
    view->saveFile();
}

void MainWindow::saveAsActionSlot(){
    GraphicsView* view = static_cast<GraphicsView*>(tabWidget->currentWidget());
    view->saveFileAs();
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

void MainWindow::settingsActionSlot(){

    settings->show();
}

void MainWindow::showObjectDockActionSlot(bool checked){

    objectWindow->setVisible(checked);
}

void MainWindow::showConnectorDockActionSlot(bool checked){

    connectorWindow->setVisible(checked);
}

void MainWindow::showHistoryDockActionSlot(bool checked){

    historyWindow->setVisible(checked);
}

void MainWindow::showPropertyDockActionSlot(bool checked){

    propertyWindow->setVisible(checked);
}

void MainWindow::setElementPlacementStatus(ElementPlacementStatus elementPlacementStatus){

    const int ghostAlpha = 50;

    this->elementPlacementStatus = elementPlacementStatus;

    QGraphicsScene* scene = static_cast<QGraphicsView*>(tabWidget->currentWidget())->scene();
    if(elementPlacementGhost != nullptr){
        scene->removeItem(elementPlacementGhost);
        delete elementPlacementGhost;
    }

    if(elementPlacementStatus == ElementPlacementStatus::connectorStartPoint){
        objectList->blockSignals(true);
        for(int i = 0; i < objectList->count(); i++){
            objectList->item(i)->setSelected(false);
        }
        objectList->blockSignals(false);
    }

    if(elementPlacementStatus == ElementPlacementStatus::object){
        connectorList->blockSignals(true);
        for(int i = 0; i < connectorList->count(); i++){
            connectorList->item(i)->setSelected(false);
        }
        connectorList->blockSignals(false);

        for(int i = 0; i < objectList->count(); i++){

            if(objectList->item(i)->type() == QGraphicsItemType::classObject){
                elementPlacementGhost = new ClassObject(QPoint(200, 150), QColor(200, 200, 200, ghostAlpha));
                scene->addItem(elementPlacementGhost);
            }
            if(objectList->item(i)->type() == QGraphicsItemType::commentObject){
                elementPlacementGhost = new CommentObject(QPoint(100, 50), QColor(200, 200, 200, ghostAlpha));
                scene->addItem(elementPlacementGhost);
            }
        }
        for(int i = 0; i < connectorList->count(); i++){
            if(connectorList->item(i)->type() == QGraphicsItemType::association){
                //Connector* connector = new Connector();
                //connector->setType(Connector::Type::association);
                //connector->setColour(Qt::black);
                //scene->addItem(elementPlacementGhost);
            }
        }
    }
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
    else {
        saveAction->setEnabled(false);
        saveAsAction->setEnabled(false);
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

void MainWindow::connectorListItemSelectionChanged(){

    setElementPlacementStatus(ElementPlacementStatus::connectorStartPoint);
}

void MainWindow::objectListItemSelectionChanged(){

    setElementPlacementStatus(ElementPlacementStatus::object);
}

void MainWindow::updateElementPlacementGhostPosition(qreal x, qreal y){

    if(elementPlacementGhost != nullptr) elementPlacementGhost->setPos(x, y);
}

void MainWindow::connectSignals(){

    connect(newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsActionSlot);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undoActionSlot);
    connect(redoAction, &QAction::triggered, this, &MainWindow::redoActionSlot);
    connect(cutAction, &QAction::triggered, this, &MainWindow::cutActionSlot);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyActionSlot);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteActionSlot);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::settingsActionSlot);
    connect(showObjectDockAction, &QAction::toggled, this, &MainWindow::showObjectDockActionSlot);
    connect(showConnectorDockAction, &QAction::toggled, this, &MainWindow::showConnectorDockActionSlot);
    connect(showHistoryDockAction, &QAction::toggled, this, &MainWindow::showHistoryDockActionSlot);
    connect(showPropertyDockAction, &QAction::toggled, this, &MainWindow::showPropertyDockActionSlot);
    connect(aboutQtAction, &QAction::triggered, this, &QApplication::aboutQt);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::tabCloseRequestedSlot);

    connect(objectList, SIGNAL(itemSelectionChanged()), this, SLOT(objectListItemSelectionChanged()));
    connect(connectorList, SIGNAL(itemSelectionChanged()), this, SLOT(connectorListItemSelectionChanged()));

}

void MainWindow::createMenus(){

    menuBar = new QMenuBar(this);

    fileMenu = new QMenu(menuBar);
    fileMenu->setTitle(tr("File"));
    editMenu = new QMenu(menuBar);
    editMenu->setTitle(tr("Edit"));
    toolsMenu = new QMenu(menuBar);
    toolsMenu->setTitle(tr("Tools"));
    viewMenu = new QMenu(menuBar);
    viewMenu->setTitle(tr("View"));
    helpMenu = new QMenu(menuBar);
    helpMenu->setTitle(tr("Help"));

    burgerMenu = new QMenu(this);
    burgerMenu->addMenu(fileMenu);
    burgerMenu->addMenu(editMenu);
    burgerMenu->addMenu(toolsMenu);
    burgerMenu->addMenu(viewMenu);
    burgerMenu->addMenu(helpMenu);

    menuButton->setMenu(burgerMenu);

    //Add fileMenu actions
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //Add editMenu actions
    menuBar->addMenu(editMenu);
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(selectAllAction);
    editMenu->addAction(selectNoneAction);

    //Add toolsMenu actions
    menuBar->addMenu(toolsMenu);
    toolsMenu->addAction(arrangeGraphAction);
    toolsMenu->addSeparator();
    toolsMenu->addAction(settingsAction);

    //Add viewMenu actions
    menuBar->addMenu(viewMenu);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(zoomResetAction);
    viewMenu->addSeparator();
    viewMenu->addAction(showObjectDockAction);
    viewMenu->addAction(showConnectorDockAction);
    viewMenu->addAction(showHistoryDockAction);
    viewMenu->addAction(showPropertyDockAction);
    viewMenu->addSeparator();
    viewMenu->addAction(showGridAction);
    viewMenu->addAction(gridSnapAction);


    //Add helpMenu actions
    menuBar->addMenu(helpMenu);
    helpMenu->addAction(helpContentsAction);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutQtAction);
    helpMenu->addAction(aboutAction);

}

void MainWindow::createToolBars(){

    fileToolBar = new QToolBar(this);
    editToolBar = new QToolBar(this);
    viewToolBar = new QToolBar(this);

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

    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    viewToolBar->addAction(zoomResetAction);
}

void MainWindow::createActions(){

    //fileMenu actions
    newAction = new QAction(QIcon::fromTheme("document-new"), tr("New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create new project"));
    openAction = new QAction(QIcon::fromTheme("document-open"), tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing project"));
    saveAction = new QAction(QIcon::fromTheme("document-save"), tr("Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save project"));
    saveAsAction = new QAction(QIcon::fromTheme("document-save-as"), tr("Save As..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save project to another location"));
    exportAction = new QAction(tr("Export"), this);
    exportAction->setStatusTip(tr("Export project to another format"));
    exitAction = new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));

    //editMenu actions
    undoAction = new QAction(QIcon::fromTheme("edit-undo"), tr("Undo"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(tr("Undo an action"));
    redoAction = new QAction(QIcon::fromTheme("edit-redo"), tr("Redo"), this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(tr("Redo an undoed action"));
    cutAction = new QAction(QIcon::fromTheme("edit-cut"), tr("Cut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut object(s)"));
    copyAction = new QAction(QIcon::fromTheme("edit-copy"), tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy object(s)"));
    pasteAction = new QAction(QIcon::fromTheme("edit-paste"), tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste object(s)"));
    selectAllAction = new QAction(QIcon::fromTheme("edit-select-all"), tr("Select All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select everything from a project"));
    selectNoneAction = new QAction(tr("Select None"), this);
    selectNoneAction->setStatusTip(tr("Make every item unselected"));

    //toolsMenu actions
    settingsAction = new QAction(tr("Settings"), this);
    settingsAction->setStatusTip(tr("Settings"));
    arrangeGraphAction = new QAction(tr("Arrange Graph"), this);
    arrangeGraphAction->setStatusTip("Arrange your project's items to a certain order");

    //viewMenu actions
    zoomInAction = new QAction(QIcon::fromTheme("zoom-in"), tr("Zoom In"), this);
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    zoomInAction->setStatusTip(tr("Zoom in"));
    zoomOutAction = new QAction(QIcon::fromTheme("zoom-out"), tr("Zoom Out"), this);
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    zoomOutAction->setStatusTip(tr("Zoom out"));
    zoomResetAction = new QAction(QIcon::fromTheme("zoom-original"), tr("Reset Zoom"), this);
    zoomResetAction->setStatusTip(tr("Reset zoom to 100%"));
    showObjectDockAction = new QAction(tr("Show Objects Window"), this);
    showObjectDockAction->setStatusTip(tr("Show/hide objects window"));
    showObjectDockAction->setCheckable(true);
    showObjectDockAction->setChecked(true);
    showConnectorDockAction = new QAction(tr("Show Connectors Window"), this);
    showConnectorDockAction->setStatusTip(tr("Show/hide connectors window"));
    showConnectorDockAction->setCheckable(true);
    showConnectorDockAction->setChecked(true);
    showHistoryDockAction = new QAction(tr("Show History Window"), this);
    showHistoryDockAction->setStatusTip(tr("Show/hide undo history window"));
    showHistoryDockAction->setCheckable(true);
    showHistoryDockAction->setChecked(true);
    showPropertyDockAction  = new QAction(tr("Show Properties Window"), this);
    showPropertyDockAction->setStatusTip(tr("Show/hide properties window"));
    showPropertyDockAction->setCheckable(true);
    showPropertyDockAction->setChecked(true);
    showGridAction = new QAction(tr("Show Grid"), this);
    showGridAction->setStatusTip(tr("Show/hide grid in the project"));
    showGridAction->setCheckable(true);
    gridSnapAction = new QAction(tr("Grid Snap"), this);
    gridSnapAction->setStatusTip(tr("Enable/disable grid snap"));
    gridSnapAction->setCheckable(true);

    //helpMenu actions
    helpContentsAction = new QAction(QIcon::fromTheme("help-contents"), tr("Help Contents"), this);
    helpContentsAction->setShortcut(QKeySequence::HelpContents);
    helpContentsAction->setStatusTip(tr("Show help document"));
    aboutQtAction = new QAction(tr("About Qt"), this);
    aboutQtAction->setStatusTip(tr("View information about Qt"));
    aboutAction = new QAction(QIcon::fromTheme("help-about"), tr("About"), this);
    aboutAction->setStatusTip(tr("View information about UMLEdit"));

}

void MainWindow::initTabWidget(){

    //Create the tab widget which displays the projects:
    tabWidget = new QTabWidget(this);
    tabWidget->setTabBarAutoHide(false);
    tabWidget->setTabsClosable(true);

    //Menu button for the alternative mode when menubar is hidden
    menuButton = new QPushButton(tabWidget);
    menuButton->setIcon(QIcon(":/image/menu_icon.svg"));
    menuButton->hide();
    //tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);

    /*Horrible hack or, as some may say, a temporary workaround
    Basically set fixed height for menubutton by creating a temporary tab
    which is immediately deleted when the value is aquired */
    QWidget* randWidget = new QWidget();

    tabWidget->addTab(randWidget, tr("Temp"));

    menuButton->setFixedSize(48, menuButton->height()-1);
    menuButton->setFlat(true);

    tabWidget->removeTab(0);
    delete randWidget;

    tabWidget->setContentsMargins(0,0,0,0);
}

void MainWindow::createDockWidgets(){

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
    objectList->addItem(new QListWidgetItem(QIcon(":/image/comm_object.svg"), tr("Comment"), objectList, QGraphicsItemType::commentObject));
    objectList->addItem(new QListWidgetItem(QIcon(":/image/class_object.svg"), tr("Class"), objectList, QGraphicsItemType::classObject));
    objectWindow->setWidget(objectList);
    objectWindow->setContentsMargins(0,0,0,0);

    connectorList = new QListWidget(objectWindow);
    connectorList->setUniformItemSizes(true);
    connectorList->setViewMode(QListView::IconMode);
    connectorList->setFrameStyle(QFrame::NoFrame);
    connectorList->addItem(new QListWidgetItem(QIcon(":/image/assoc_arrow.svg"), tr("Arrow"), connectorList, QGraphicsItemType::association));
    connectorWindow->setWidget(connectorList);
    connectorWindow->setContentsMargins(0,0,0,0);

    historyView = new QUndoView(historyWindow);
    historyView->setFrameStyle(QFrame::NoFrame);
    historyWindow->setWidget(historyView);
    historyWindow->setContentsMargins(0,0,0,0);

    propertyWindow->setContentsMargins(0,0,0,0);
    selectionLabel = new QLabel(propertyWindow);
    selectionLabel->setText(tr("No item(s) selected."));
    propertyWindow->setWidget(selectionLabel);
}

void MainWindow::updateStatusBarCoordinates(qreal x, qreal y){

    coordinatesLabel->setText(QString("(%1,%2)").arg(x).arg(y));
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("UMLedit");

    settings = new SettingsWindow(this);

    newProjectCount = 0;

    statusBar = new QStatusBar(this);
    coordinatesLabel = new QLabel(statusBar);
    statusBar->addWidget(coordinatesLabel);

    initTabWidget();
    createActions();
    createMenus();
    createToolBars();
    createDockWidgets();

    //Set created widgets to mainwindow:
    setMenuBar(menuBar);
    setStatusBar(statusBar);
    addToolBar(fileToolBar);
    addToolBar(editToolBar);
    addToolBar(viewToolBar);
    setCentralWidget(tabWidget);

    saveAction->setEnabled(false);
    saveAsAction->setEnabled(false);
    connectSignals();
    this->showMaximized();

    elementPlacementGhost = nullptr;

}

MainWindow::~MainWindow(){

}
