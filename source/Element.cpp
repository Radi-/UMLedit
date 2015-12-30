
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

    groupPropertyManager.reset(new QtGroupPropertyManager());
    colorPropertyManager.reset(new QtColorPropertyManager());
    pointPropertyManager.reset(new QtPointPropertyManager());

    spinBoxFactory.reset(new QtSpinBoxFactory());
    colorFactory.reset(new QtColorEditorFactory());

    propertyBrowser.data()->setFactoryForManager(colorPropertyManager.data(), colorFactory.data());
    propertyBrowser.data()->setFactoryForManager(pointPropertyManager.data()->subIntPropertyManager(), spinBoxFactory.data());
    propertyBrowser.data()->setFactoryForManager(colorPropertyManager.data()->subIntPropertyManager(), spinBoxFactory.data());

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);

    colorPropertyManager.reset(new QtColorPropertyManager(this));

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    colour = colorPropertyManager.data()->addProperty("Colour");
    elementGroup = groupPropertyManager.data()->addProperty("Element");

    elementGroup->addSubProperty(this->colour);
    elementGroup->addSubProperty(sizep);

    propertyBrowser.data()->addProperty(elementGroup);

    connect(pointPropertyManager.data(), SIGNAL(valueChanged(QtProperty*,QPoint)), this, SLOT(pointPropertyUpdated(QtProperty*,QPoint)));
    connect(colorPropertyManager.data(), SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(updateDrawingParameters()));
}

Element::~Element(){
}

void Element::pointPropertyUpdated(QtProperty* property, QPoint size){

    if (property == sizep){
        updateDrawingParameters();
        setSize(size);
    }
    else if (property == this->size && (pointPropertyManager.data()->value(this->size).x() != pointPropertyManager.data()->value(sizep).x() ||
                                  pointPropertyManager.data()->value(this->size).y() != pointPropertyManager.data()->value(sizep).y())){
        pointPropertyManager.data()->blockSignals(true);
        pointPropertyManager->setValue(sizep, size);

        pointPropertyManager.data()->blockSignals(false);
    }
}

void Element::updateDrawingParameters(){

}

void Element::setColour(QColor colour){

    colorPropertyManager->setValue(this->colour, colour);
}
