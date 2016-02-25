
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

void MainWindow::keyPressEvent(QKeyEvent* event){

    if(tabletModeEnabled){
        if(tabWidget->count() > 0){

            switch (event->key()){

            case Qt::Key_Q:
                updateTabletModeTabWidget(Qt::Key_Q);
                break;
            case Qt::Key_W:
                updateTabletModeTabWidget(Qt::Key_W);
                break;
            default:
                event->ignore();
                break;
            }

        }
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

    connect(scene, &GraphicsScene::cursorPositionChanged, this, &MainWindow::updateStatusBarCoordinates);
    connect(scene, &GraphicsScene::selectionChanged, this, &MainWindow::setPropertyBrowser);
    connect(scene, &GraphicsScene::cursorPositionChanged, this, &MainWindow::updateElementPlacementGhostPosition);
    connect(scene, &GraphicsScene::mouseClicked, this, &MainWindow::placeElement);

    view->setScene(scene);
    view->setContextMenu(contextMenu);

    tabWidget->addTab(view, tr("Project %1").arg(newProjectCount));
    tabWidget->setCurrentIndex(tabWidget->count()-1);

    //test objects:
    /*
    CommentObject* commentObject = new CommentObject();
    commentObject->setPos(QPointF(0, 0));
    commentObject->setSize(QPoint(100, 50));
    commentObject->setColour(QColor(200, 200, 0, 255));
    scene->addItem(commentObject);

    ClassObject* classObject = new ClassObject();
    classObject->setPos(QPointF(100, 100));
    classObject->setSize(QPoint(200, 150));
    classObject->setColour(QColor(200, 200, 200, 255));
    scene->addItem(classObject);

    Connector* connector = new Connector();
    connector->setPos(QPoint(100,100));
    connector->setEndPoint(QPoint(200, 200));
    connector->setType(Connector::Type::dependency);
    connector->setColour(Qt::black);  
    scene->addItem(connector);

    commentObject->connectConnectorStartPoint(Connection(connector, QPointF(0, 0)));
    classObject->connectConnectorEndPoint(Connection(connector, QPointF(0, 0)));
    */

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

void MainWindow::setListUnselected(QListWidget* list){

    list->blockSignals(true);
    list->clearSelection();
    list->blockSignals(false);
}

void MainWindow::setElementPlacementStatus(ElementPlacementStatus elementPlacementStatus){

    if(tabWidget->count() > 0){

        const int ghostAlpha = 50;

        this->elementPlacementStatus = elementPlacementStatus;

        QGraphicsScene* scene = static_cast<QGraphicsView*>(tabWidget->currentWidget())->scene();

        if(elementPlacementGhost != nullptr){
            scene->removeItem(elementPlacementGhost);
            delete elementPlacementGhost;
        }

        if(elementPlacementStatus == ElementPlacementStatus::connectorStartPoint){

            setListUnselected(objectList);

            if(tabletModeEnabled){
                if(connectorListTabletMode->currentItem()->type() == ElementType::association){
                    elementPlacementGhost = new Connector();
                    static_cast<Connector*>(elementPlacementGhost)->setType(Connector::Type::association);
                    setListUnselected(connectorList);
                }
            }
            else{
                if(connectorList->currentItem()->type() == ElementType::association){
                    elementPlacementGhost = new Connector();
                    static_cast<Connector*>(elementPlacementGhost)->setType(Connector::Type::association);
                }
            }

            elementPlacementGhost->setAlpha(ghostAlpha);
            scene->addItem(elementPlacementGhost);
        }

        if(elementPlacementStatus == ElementPlacementStatus::object){

            setListUnselected(connectorList);

            if(tabletModeEnabled){
                if(objectListTabletMode->currentItem()->type() == ElementType::classObject){
                    elementPlacementGhost = new ClassObject();
                }
                else if(objectListTabletMode->currentItem()->type() == ElementType::commentObject){
                    elementPlacementGhost = new CommentObject();
                }
                setListUnselected(objectList);
            }
            else{
                if(objectList->currentItem()->type() == ElementType::classObject){
                    elementPlacementGhost = new ClassObject();
                }
                else if(objectList->currentItem()->type() == ElementType::commentObject){
                    elementPlacementGhost = new CommentObject();
                }
            }

            elementPlacementGhost->setAlpha(ghostAlpha);
            scene->addItem(elementPlacementGhost);
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

    if(tabWidget->count() > 0 && !propertyWindow.isNull()){
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
}

void MainWindow::connectorListItemSelectionChanged(){

    setElementPlacementStatus(ElementPlacementStatus::connectorStartPoint);
    tabletModeTabWidget->hide();
}

void MainWindow::connectorListTabletModeItemSelectionChanged(){

    setElementPlacementStatus(ElementPlacementStatus::connectorStartPoint);
    tabletModeTabWidget->hide();
}

void MainWindow::objectListItemSelectionChanged(){

    setElementPlacementStatus(ElementPlacementStatus::object);
    tabletModeTabWidget->hide();
}

void MainWindow::objectListTabletModeItemSelectionChanged(){

    setElementPlacementStatus(ElementPlacementStatus::object);
    tabletModeTabWidget->hide();
}

void MainWindow::updateElementPlacementGhostPosition(qreal x, qreal y){

    if(elementPlacementGhost != nullptr){
        if(elementPlacementStatus == ElementPlacementStatus::object){
            elementPlacementGhost->setPos(x, y);
        }
        else if(elementPlacementStatus == ElementPlacementStatus::connectorStartPoint){
            elementPlacementGhost->setPos(x, y);
            static_cast<Connector*>(elementPlacementGhost)->setEndPoint(QPoint(x, y));
        }
        else if(elementPlacementStatus == ElementPlacementStatus::connectorEndPoint){
            static_cast<Connector*>(elementPlacementGhost)->setEndPoint(QPoint(x, y));
        }
    }
}

void MainWindow::placeElement(Qt::MouseButton mouseButton){

    if(elementPlacementStatus == ElementPlacementStatus::connectorStartPoint){
        elementPlacementStatus = ElementPlacementStatus::connectorEndPoint;
    }
    else if(elementPlacementStatus == ElementPlacementStatus::connectorEndPoint ||
            elementPlacementStatus == ElementPlacementStatus::object){
        elementPlacementGhost->setAlpha(255);
        elementPlacementStatus = ElementPlacementStatus::none;
        elementPlacementGhost = nullptr;
    }

    setListUnselected(objectList);
    setListUnselected(objectListTabletMode);
    setListUnselected(connectorList);
    setListUnselected(connectorListTabletMode);
    tabletModeTabWidget->hide();

    static_cast<QGraphicsView*>(tabWidget->currentWidget())->scene()->update();
}

void MainWindow::updateTabletModeTabWidget(Qt::Key key){

    QPoint viewPos = QCursor::pos() + QPoint(0, -20);

    tabletModeTabWidget->show();
    tabletModeTabWidget->raise();
    tabletModeTabWidget->move(viewPos);

    if(key == Qt::Key_Q){
        tabletModeTabWidget->setCurrentIndex(0);
    }
    else if(key == Qt::Key_W){
        tabletModeTabWidget->setCurrentIndex(1);
    }

    setListUnselected(objectList);
    setListUnselected(objectListTabletMode);
    setListUnselected(connectorList);
    setListUnselected(connectorListTabletMode);
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

    connect(objectList, &QListWidget::itemSelectionChanged, this, &MainWindow::objectListItemSelectionChanged);
    connect(objectListTabletMode, &QListWidget::itemSelectionChanged, this, &MainWindow::objectListTabletModeItemSelectionChanged);
    connect(connectorList, &QListWidget::itemSelectionChanged, this, &MainWindow::connectorListItemSelectionChanged);
    connect(connectorListTabletMode, &QListWidget::itemSelectionChanged, this, &MainWindow::connectorListTabletModeItemSelectionChanged);

    connect(settings, &SettingsWindow::alternateModeCheckBoxToggled, this, &MainWindow::setDrawingTabletModeOn);
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

    //Create contextMenu
    contextMenu = new QMenu(this);
    contextMenu->addAction(cutAction);
    contextMenu->addAction(copyAction);
    contextMenu->addAction(pasteAction);

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
    newAction = new QAction(QIcon::fromTheme("document-new", QIcon(":/image/document-new.svg")), tr("New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create new project"));
    openAction = new QAction(QIcon::fromTheme("document-open", QIcon(":/image/document-open.svg")), tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing project"));
    saveAction = new QAction(QIcon::fromTheme("document-save", QIcon(":/image/document-save.svg")), tr("Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save project"));
    saveAction->setDisabled(true);
    saveAsAction = new QAction(QIcon::fromTheme("document-save-as", QIcon(":/image/document-save-as.svg")), tr("Save As..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save project to another location"));
    saveAsAction->setDisabled(true);
    exportAction = new QAction(tr("Export"), this);
    exportAction->setStatusTip(tr("Export project to another format"));
    exportAction->setDisabled(true);
    exitAction = new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));

    //editMenu actions
    undoAction = new QAction(QIcon::fromTheme("edit-undo", QIcon(":/image/edit-undo.svg")), tr("Undo"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(tr("Undo an action"));
    undoAction->setDisabled(true);
    redoAction = new QAction(QIcon::fromTheme("edit-redo", QIcon(":/image/edit-redo.svg")), tr("Redo"), this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(tr("Redo an undoed action"));
    redoAction->setDisabled(true);
    cutAction = new QAction(QIcon::fromTheme("edit-cut", QIcon(":/image/edit-cut.svg")), tr("Cut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut object(s)"));
    cutAction->setDisabled(true);
    copyAction = new QAction(QIcon::fromTheme("edit-copy", QIcon(":/image/edit-copy.svg")), tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy object(s)"));
    copyAction->setDisabled(true);
    pasteAction = new QAction(QIcon::fromTheme("edit-paste", QIcon(":/image/edit-paste.svg")), tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste object(s)"));
    pasteAction->setDisabled(true);
    selectAllAction = new QAction(QIcon::fromTheme("edit-select-all", QIcon(":/image/edit-select-all.svg")), tr("Select All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select everything from a project"));
    selectAllAction->setDisabled(true);
    selectNoneAction = new QAction(tr("Select None"), this);
    selectNoneAction->setStatusTip(tr("Make every item unselected"));
    selectNoneAction->setDisabled(true);

    //toolsMenu actions
    settingsAction = new QAction(tr("Settings"), this);
    settingsAction->setStatusTip(tr("Settings"));
    arrangeGraphAction = new QAction(tr("Arrange Graph"), this);
    arrangeGraphAction->setStatusTip("Arrange your project's items to a certain order");
    arrangeGraphAction->setDisabled(true);

    //viewMenu actions
    zoomInAction = new QAction(QIcon::fromTheme("zoom-in", QIcon(":/image/View-zoom-in.svg")), tr("Zoom In"), this);
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    zoomInAction->setStatusTip(tr("Zoom in"));
    zoomInAction->setDisabled(true);
    zoomOutAction = new QAction(QIcon::fromTheme("zoom-out", QIcon(":/image/View-zoom-out.svg")), tr("Zoom Out"), this);
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    zoomOutAction->setStatusTip(tr("Zoom out"));
    zoomOutAction->setDisabled(true);
    zoomResetAction = new QAction(QIcon::fromTheme("zoom-original", QIcon(":/image/View-zoom-fit.svg")), tr("Reset Zoom"), this);
    zoomResetAction->setStatusTip(tr("Reset zoom to 100%"));
    zoomResetAction->setDisabled(true);
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
    showGridAction->setDisabled(true);
    gridSnapAction = new QAction(tr("Grid Snap"), this);
    gridSnapAction->setStatusTip(tr("Enable/disable grid snap"));
    gridSnapAction->setCheckable(true);
    gridSnapAction->setDisabled(true);

    //helpMenu actions
    helpContentsAction = new QAction(QIcon::fromTheme("help-contents"), tr("Help Contents"), this);
    helpContentsAction->setShortcut(QKeySequence::HelpContents);
    helpContentsAction->setStatusTip(tr("Show help document"));
    aboutQtAction = new QAction(tr("About Qt"), this);
    aboutQtAction->setStatusTip(tr("View information about Qt"));
    aboutAction = new QAction(QIcon::fromTheme("help-about"), tr("About"), this);
    aboutAction->setStatusTip(tr("View information about UMLEdit"));

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
    objectList->addItem(new QListWidgetItem(QIcon(":/image/comm_object.svg"), tr("Comment"), objectList, ElementType::commentObject));
    objectList->addItem(new QListWidgetItem(QIcon(":/image/class_object.svg"), tr("Class"), objectList, ElementType::classObject));
    objectWindow->setWidget(objectList);
    objectWindow->setContentsMargins(0,0,0,0);

    connectorList = new QListWidget(objectWindow);
    connectorList->setUniformItemSizes(true);
    connectorList->setViewMode(QListView::IconMode);
    connectorList->setFrameStyle(QFrame::NoFrame);
    connectorList->addItem(new QListWidgetItem(QIcon(":/image/assoc_arrow.svg"), tr("Arrow"), connectorList, ElementType::association));
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

void MainWindow::initTabWidget(){

    //Create the tab widget which displays the projects:
    tabWidget = new QTabWidget(this);
    tabWidget->setTabBarAutoHide(false);
    tabWidget->setTabsClosable(true);

    //Menu button for the alternative mode when menubar is hidden
    menuButton = new QPushButton(tabWidget);
    menuButton->setIcon(QIcon(":/image/menu_icon.svg"));
    menuButton->hide();

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

void MainWindow::createTabletModeWidgets(){

    int padding = 20;

    objectListTabletMode = new QListWidget(this);
    objectListTabletMode->setUniformItemSizes(true);
    objectListTabletMode->setGridSize(QSize(50, 60));
    objectListTabletMode->setWordWrap(true);
    objectListTabletMode->setViewMode(QListView::IconMode);
    objectListTabletMode->addItem(new QListWidgetItem(QIcon(":/image/comm_object.svg"), tr("Comment"), objectListTabletMode, ElementType::commentObject));
    objectListTabletMode->addItem(new QListWidgetItem(QIcon(":/image/class_object.svg"), tr("Class"), objectListTabletMode, ElementType::classObject));
    objectListTabletMode->setWrapping(false);

    connectorListTabletMode = new QListWidget(this);
    connectorListTabletMode->setUniformItemSizes(true);
    connectorListTabletMode->setGridSize(QSize(50, 60));
    connectorListTabletMode->setWordWrap(true);
    connectorListTabletMode->setViewMode(QListView::IconMode);
    connectorListTabletMode->addItem(new QListWidgetItem(QIcon(":/image/assoc_arrow.svg"), tr("Arrow"), connectorListTabletMode, ElementType::association));
    connectorListTabletMode->setWrapping(false);

    tabletModeTabWidget = new QTabWidget(this);
    tabletModeTabWidget->addTab(objectListTabletMode, tr("Objects"));
    tabletModeTabWidget->addTab(connectorListTabletMode, tr("Connectors"));
    tabletModeTabWidget->resize(200, 100);
    tabletModeTabWidget->hide();
}

void MainWindow::updateStatusBarCoordinates(qreal x, qreal y){

    coordinatesLabel->setText(QString("(%1,%2)").arg(x).arg(y));
}

void MainWindow::setDrawingTabletModeOn(bool enabled){

    tabletModeEnabled = enabled;

    if (enabled){
        menuBar->hide();
        fileToolBar->hide();
        editToolBar->hide();
        viewToolBar->hide();
        objectWindow->hide();
        connectorWindow->hide();
        propertyWindow->hide();
        historyWindow->hide();
        tabWidget->setCornerWidget(menuButton, Qt::TopLeftCorner);
        menuButton->show();
    }
    else{
        menuBar->show();
        fileToolBar->show();
        editToolBar->show();
        viewToolBar->show();
        objectWindow->show();
        connectorWindow->show();
        propertyWindow->show();
        historyWindow->show();
        menuButton->hide();
        tabWidget->setCornerWidget(0, Qt::TopLeftCorner);
        tabletModeTabWidget->hide();
    }
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
    createTabletModeWidgets();

    //Set created widgets to mainwindow:
    setMenuBar(menuBar);
    setStatusBar(statusBar);
    addToolBar(fileToolBar);
    addToolBar(editToolBar);
    addToolBar(viewToolBar);
    setCentralWidget(tabWidget);
    connectSignals();
    this->showMaximized();

    elementPlacementStatus = ElementPlacementStatus::none;
    elementPlacementGhost = nullptr;

    setDrawingTabletModeOn(false);

}

MainWindow::~MainWindow(){

}
