
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

    colorPropertyManager = new QtColorPropertyManager(this);
    pointPropertyManager = new QtPointPropertyManager(this);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    size = pointPropertyManager.data()->addProperty("Actual Size");
    sizep = pointPropertyManager.data()->addProperty("Size");
    colour = colorPropertyManager.data()->addProperty("Colour");
}

Element::~Element(){
}

void Element::setSize(QPoint size){

    if( pointPropertyManager->value(this->size).x() != size.x() ||  pointPropertyManager->value(this->size).y() != size.y()){
        prepareGeometryChange();
        pointPropertyManager->setValue(this->size, size);
        update();
    }
}

void Element::setColour(QColor colour){

    colorPropertyManager->setValue(this->colour, colour);

}

QRectF Element::boundingRect() const{

    return QRectF(0, 0, pointPropertyManager->value(this->size).x(), pointPropertyManager->value(this->size).y());
}
