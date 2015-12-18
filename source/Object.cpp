
#include "header/Object.h"

QRectF Object::boundingRect() const{

    return QRectF(0, 0, 110, 70);
}

QPainterPath Object::shape() const{

    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void Object::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){


    //QBrush b = painter->brush();
    painter->setBrush(colour);
    painter->drawRect(13, 13, 97, 57);
    //painter->setBrush(b);
}
