
#include "header/Object.h"

void Object::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    //TODO: move connector start- and endpoints
    event->pos();
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

void Object::connectConnectorStartPoint(Connector* connector){

    for(int i = 0; i < startPointConnectors.size(); i++){
        if(startPointConnectors.at(i) == connector) return;
    }
    startPointConnectors.push_back(connector);
}

void Object::disconnectConnectorStartPoint(Connector* connector){

    for(int i = 0; i < startPointConnectors.size(); i++){
        if(startPointConnectors.at(i) == connector){
            startPointConnectors.removeAt(i);
            break;
        }
    }
}

void Object::connectConnectorEndPoint(Connector* connector){

    for(int i = 0; i < startPointConnectors.size(); i++){
        if(startPointConnectors.at(i) == connector) return;
    }
    startPointConnectors.push_back(connector);
}

void Object::disconnectConnectorEndPoint(Connector* connector){

    for(int i = 0; i < startPointConnectors.size(); i++){
        if(startPointConnectors.at(i) == connector){
            startPointConnectors.removeAt(i);
            break;
        }
    }
}

QRectF Object::boundingRect() const{

    return QRectF(0, 0, pointPropertyManager->value(this->size).x(), pointPropertyManager->value(this->size).y());
}
