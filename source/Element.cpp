
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

    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);

    propertyBrowser.reset(new QtTreePropertyBrowser());

    groupPropertyManager.reset(new QtGroupPropertyManager());
    colorPropertyManager.reset(new QtColorPropertyManager());

    spinBoxFactory.reset(new QtSpinBoxFactory());
    colorFactory.reset(new QtColorEditorFactory());

    propertyBrowser.data()->setFactoryForManager(colorPropertyManager.data(), colorFactory.data());
    propertyBrowser.data()->setFactoryForManager(colorPropertyManager.data()->subIntPropertyManager(), spinBoxFactory.data());

    colorPropertyManager.reset(new QtColorPropertyManager(this));

    setAcceptHoverEvents(true);

    colour = colorPropertyManager.data()->addProperty("Colour");
    elementGroup = groupPropertyManager.data()->addProperty("Element");

    elementGroup->addSubProperty(this->colour);

    propertyBrowser.data()->addProperty(elementGroup);
}

Element::~Element(){
}

void Element::setColour(QColor colour){

    colorPropertyManager->setValue(this->colour, colour);
}
