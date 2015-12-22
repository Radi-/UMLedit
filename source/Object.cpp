
#include "header/Object.h"

void Object::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    //TODO: move connector start- and endpoints
    //event->pos();
    Element::mouseMoveEvent(event);
}

Object::Object(QGraphicsItem* parent) : Element(parent){
}

Object::~Object(){
}
