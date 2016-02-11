
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

    propertyBrowser = new QtTreePropertyBrowser();

    groupPropertyManager.reset(new QtGroupPropertyManager());
    colorPropertyManager.reset(new QtColorPropertyManager());

    spinBoxFactory.reset(new QtSpinBoxFactory());
    colorFactory.reset(new QtColorEditorFactory());

    propertyBrowser->setFactoryForManager(colorPropertyManager.data(), colorFactory.data());
    propertyBrowser->setFactoryForManager(colorPropertyManager->subIntPropertyManager(), spinBoxFactory.data());

    colour = colorPropertyManager.data()->addProperty("Colour");
    elementGroup = groupPropertyManager.data()->addProperty("Element");

    elementGroup->addSubProperty(this->colour);

    propertyBrowser.data()->addProperty(elementGroup);
}

Element::~Element(){
    if (!propertyBrowser.isNull()){
       delete propertyBrowser;
    }
}

void Element::setColour(QColor colour){

    colorPropertyManager->setValue(this->colour, colour);
}

void Element::setAlpha(unsigned int alpha){

    QColor colour = colorPropertyManager->value(this->colour);
    colour.setAlpha(alpha);
    colorPropertyManager->setValue(this->colour, colour);
}
