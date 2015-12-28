
#include "header/CommentObject.h"

CommentObject::CommentObject(){
}

CommentObject::CommentObject(QPoint size, QColor colour){

    pointPropertyManager->setValue(this->size, size);
    this->colour = colour;
    string = "comment";
    font = QFont("Sans", 10);
}

CommentObject::~CommentObject(){
}

void CommentObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(colour);

    const QPoint points[5] = {
        QPoint(0, 0),
        QPoint(0, pointPropertyManager->value(size).y()),
        QPoint(pointPropertyManager->value(size).x(), pointPropertyManager->value(size).y()),
        QPoint(pointPropertyManager->value(size).x(), 20),
        QPoint(pointPropertyManager->value(size).x() - 20, 0)
    };
    painter->drawConvexPolygon(points, 5);

    painter->drawLine(pointPropertyManager->value(size).x(), 20, pointPropertyManager->value(size).x() - 20, 20);
    painter->drawLine(pointPropertyManager->value(size).x() - 20, 0, pointPropertyManager->value(size).x() - 20, 20);

    //painter->drawLine(0, size.y() * 0.5, size.x(), size.y() * 0.5);

    painter->setFont(font);
    painter->drawText(QRect(0, 0, pointPropertyManager->value(size).x(), pointPropertyManager->value(size).y()), Qt::AlignCenter | Qt::TextWordWrap, string);
}

QtTreePropertyBrowser* CommentObject::getPropertyBrowser(){
    return propertyBrowser;
}

