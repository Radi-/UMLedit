
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

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    sizep = pointPropertyManager->addProperty(tr("Size"));
    colourp = colorPropertyManager->addProperty(tr("Colour"));
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
