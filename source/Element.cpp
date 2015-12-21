
#include "header/Element.h"

Element::Element(){
}

Element::~Element(){
}

void Element::setSize(QPoint size){

    if(this->size.x() != size.x() || this->size.y() != size.y()){
        prepareGeometryChange();
        this->size = size;
    }
}

void Element::setColour(QColor colour){

    this->colour = colour;
}

QRectF Element::boundingRect() const{

    return QRectF(0, 0, size.x(), size.y());
}
