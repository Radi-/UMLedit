
#include "header/Connector.h"

Connector::Connector(){

    boundingRectPadding = 50;
}

Connector::~Connector(){
}

void Connector::setType(Type type){

    this->type = type;
}

void Connector::setEndPoint(QPoint endPoint){

    this->endPoint = endPoint;
}

QtTreePropertyBrowser* Connector::getPropertyBrowser(){
    return propertyBrowser.data();
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

QRectF Connector::boundingRect() const{

    QPointF vector = endPoint - pos();

    if(vector.x() > 0){
        if(vector.y() > 0) return QRectF(-boundingRectPadding, -boundingRectPadding, vector.x() + boundingRectPadding, vector.y() + boundingRectPadding);
        return QRectF(-boundingRectPadding, boundingRectPadding, vector.x() + boundingRectPadding, vector.y() - boundingRectPadding);
    }
    if(vector.x() > 0){
        if(vector.y() > 0) return QRectF(boundingRectPadding, -boundingRectPadding, vector.x() - boundingRectPadding, vector.y() + boundingRectPadding);
        return QRectF(boundingRectPadding, boundingRectPadding, vector.x() - boundingRectPadding, vector.y() - boundingRectPadding);
    }
}

