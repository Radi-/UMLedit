
#include "header/CommentObject.h"

CommentObject::CommentObject(){
}

CommentObject::CommentObject(QPoint size, QColor colour){

    this->size = size;
    this->colour = colour;
    string = "comment";
    font = QFont("Sans", 10);
}

CommentObject::~CommentObject(){
}

void CommentObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    painter->setBrush(colour);

    const QPoint points[5] = {
        QPoint(0, 0),
        QPoint(0, size.y()),
        QPoint(size.x(), size.y()),
        QPoint(size.x(), 20),
        QPoint(size.x() - 20, 0)
    };
    painter->drawConvexPolygon(points, 5);

    painter->drawLine(size.x(), 20, size.x() - 20, 20);
    painter->drawLine(size.x() - 20, 0, size.x() - 20, 20);

    //painter->drawLine(0, size.y() * 0.5, size.x(), size.y() * 0.5);

    painter->setFont(font);
    painter->drawText(QRect(0, 0, size.x(), size.y()), Qt::AlignCenter | Qt::TextWordWrap, string);
}

