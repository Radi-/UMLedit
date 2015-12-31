
#include "header/Object.h"

void Object::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    //TODO: change implementation as needed when Connector uses node-objects for start- and endpoints
    //event->pos()

    Connection connection;

    for(int i = 0; i < startPointConnections.size(); i++){
        connection = startPointConnections.at(i);
        connection.connector->setPos(pos() + connection.connectionPoint);
    }
    for(int i = 0; i < endPointConnections.size(); i++){
        connection = endPointConnections.at(i);
        connection.connector->setEndPoint(pos() + connection.connectionPoint);
    }

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

    setFlags(ItemIsSelectable | ItemIsMovable);

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

void Object::connectConnectorStartPoint(Connection connection){

    for(int i = 0; i < startPointConnections.size(); i++){
        if(startPointConnections.at(i).connector == connection.connector) return;
    }
    startPointConnections.push_back(connection);
}

void Object::disconnectConnectorStartPoint(Connection connection){

    for(int i = 0; i < startPointConnections.size(); i++){
        if(startPointConnections.at(i).connector == connection.connector){
            startPointConnections.removeAt(i);
            break;
        }
    }
}

void Object::connectConnectorEndPoint(Connection connection){

    for(int i = 0; i < endPointConnections.size(); i++){
        if(endPointConnections.at(i).connector == connection.connector) return;
    }
    endPointConnections.push_back(connection);
}

void Object::disconnectConnectorEndPoint(Connection connection){

    for(int i = 0; i < endPointConnections.size(); i++){
        if(endPointConnections.at(i).connector == connection.connector){
            endPointConnections.removeAt(i);
            return;
        }
    }
}

QRectF Object::boundingRect() const{

    return QRectF(0, 0, pointPropertyManager->value(this->size).x(), pointPropertyManager->value(this->size).y());
}
