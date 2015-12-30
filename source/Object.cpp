
#include "header/Object.h"

void Object::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    //TODO: move connector start- and endpoints
    //event->pos();
    Element::mouseMoveEvent(event);
}

Object::Object(){

    pointPropertyManager.reset(new QtPointPropertyManager(this));
    size = pointPropertyManager.data()->addProperty("Actual Size");
    sizep = pointPropertyManager.data()->addProperty("Size");
}

Object::~Object(){
}

void Object::setSize(QPoint size){

    if( pointPropertyManager->value(this->size).x() != size.x() ||  pointPropertyManager->value(this->size).y() != size.y()){
        prepareGeometryChange();
        pointPropertyManager->setValue(this->size, size);
        update();
    }
}

QRectF Object::boundingRect() const{

    return QRectF(0, 0, pointPropertyManager->value(this->size).x(), pointPropertyManager->value(this->size).y());
}
