
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "header/GraphicsScene.h"

GraphicsScene::GraphicsScene(QWidget *parent) : QGraphicsScene(parent)
{
}

GraphicsScene::~GraphicsScene(){

}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    emit cursorPositionChanged(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    mouseEvent->accept();
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    emit mouseClicked(mouseEvent->button());
    mouseEvent->accept();
}
