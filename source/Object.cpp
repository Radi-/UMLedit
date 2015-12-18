
#include "header/Object.h"

QRectF Chip::boundingRect() const{

    return QRectF(0, 0, 110, 70);
}

QPainterPath Chip::shape() const{

    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void Object::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){


}
