
#include "header/Connector.h"

Connector::Connector(){
}

Connector::~Connector(){
}

void Connector::setEndPoint(QPoint endPoint){

    this->endPoint = endPoint;
}

QPainterPath Connector::shape() const{

    QPainterPath path;
    path.lineTo(endPoint);
    return path;
}
