
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

    propertyBrowser.reset(new QtTreePropertyBrowser());
    colorPropertyManager.reset(new QtColorPropertyManager(this));

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    colour = colorPropertyManager.data()->addProperty("Colour");
}

Element::~Element(){
}

void Element::setColour(QColor colour){

    colorPropertyManager->setValue(this->colour, colour);
}
