
#include "header/Element.h"


void Element::mousePressEvent(QGraphicsSceneMouseEvent* event){

    QGraphicsItem::mousePressEvent(event);
    update();
}

void Element::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    if (event->modifiers() & Qt::ShiftModifier){
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Element::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){

    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

Element::Element(){

    colorPropertyManager = new QtColorPropertyManager(0);
    pointPropertyManager = new QtPointPropertyManager(0);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    sizep = pointPropertyManager->addProperty("Size");
    colourp = colorPropertyManager->addProperty("Colour");
}

Element::~Element(){
}

void Element::setSize(QPoint size){

    if(this->size.x() != size.x() || this->size.y() != size.y()){
        prepareGeometryChange();
        this->size = size;
        pointPropertyManager->setValue(sizep, size);
    }
}

void Element::setColour(QColor colour){

    this->colour = colour;
    colorPropertyManager->setValue(colourp, colour);

}

QRectF Element::boundingRect() const{

    return QRectF(0, 0, size.x(), size.y());
}
