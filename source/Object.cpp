
#include "header/Object.h"

void Object::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    //TODO: move connector start- and endpoints
    event->pos();
    Element::mouseMoveEvent(event);
}

void Object::pointPropertyUpdated(QtProperty* property, QPoint size){

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

void Object::updateDrawingParameters(){

}

Object::Object(){

    pointPropertyManager.reset(new QtPointPropertyManager(this));

    size = pointPropertyManager->addProperty("Actual Size");
    sizep = pointPropertyManager->addProperty("Size");
    objectGroup = groupPropertyManager->addProperty("Object");

    objectGroup->addSubProperty(sizep);

    propertyBrowser->setFactoryForManager(pointPropertyManager->subIntPropertyManager(), spinBoxFactory.data());
    propertyBrowser->addProperty(objectGroup);

    connect(pointPropertyManager.data(), SIGNAL(valueChanged(QtProperty*,QPoint)), this, SLOT(pointPropertyUpdated(QtProperty*,QPoint)));
    connect(colorPropertyManager.data(), SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(updateDrawingParameters()));
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
