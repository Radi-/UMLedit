
#include "header/Connector.h"

Connector::Connector(){
}

Connector::~Connector(){
}

void Connector::setType(Type type){

    this->type = type;
}

void Connector::setEndPoint(QPoint endPoint){

    this->endPoint = endPoint;
}

QPainterPath Connector::shape() const{

    QPainterPath path;
    path.moveTo(pos());
    path.lineTo(endPoint);
    return path;
}

void Connector::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(colorPropertyManager->value(colour), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    if(type == Type::realization || type == Type::dependency) pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    painter->drawLine(QPoint(0, 0), endPoint - pos());
}

QtTreePropertyBrowser* Connector::getPropertyBrowser(){
    return propertyBrowser;
}
