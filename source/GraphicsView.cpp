
#include <QMessageBox>
#include <QFileDialog>

#include "header/GraphicsView.h"

GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent){

    filePath = QString();
    changed = false;
}

GraphicsView::GraphicsView(QString& path, QWidget* parent) : QGraphicsView(parent){

    filePath = path;
    changed = false;
}

GraphicsView::~GraphicsView(){

}

QString GraphicsView::getFilePath(){
    return filePath;
}

void GraphicsView::setFilePath(QString& path){
    filePath = path;
}

bool GraphicsView::saveFile(){
    QString savePath;

    if(filePath == QString()){
        savePath = QFileDialog::getSaveFileName(0, tr("Save"), QString(), tr("UMLedit Files (*.uef);;"
                                                                                      "All Files (*.*)"));
    }
    else savePath = filePath;

    if(!savePath.isEmpty()){
        //File writing here
        changed = false;
        return true;
    }

    return false;
}

bool GraphicsView::saveFileAs(){
    QString savePath = QFileDialog::getSaveFileName(0, tr("Save"), QString(), tr("UMLedit Files (*.uef);;"
                                                                                        "All Files (*.*)"));

    if(!savePath.isEmpty()){
        //File writing here
        changed = false;
        filePath = savePath;
        return true;
    }

    return false;
}

bool GraphicsView::hasChanged(){
    return changed;
}


void GraphicsView::setContextMenu(QMenu* contextMenu){
    this->contextMenu = contextMenu;
}

void GraphicsView::contextMenuEvent(QContextMenuEvent* event){
    QGraphicsView::contextMenuEvent(event);
    contextMenu->exec(event->globalPos());
}
