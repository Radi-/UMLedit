
#include "header/CommentObject.h"

CommentObject::CommentObject(){
}

CommentObject::CommentObject(QPoint size, QColor colour){

    stringPropertyManager.reset(new QtStringPropertyManager(this));
    fontPropertyManager.reset(new QtFontPropertyManager(this));

    string = stringPropertyManager->addProperty("Text");
    font = fontPropertyManager->addProperty("Font");

    fontPropertyManager.data()->setValue(this->font, QFont("Sans", 10));
    stringPropertyManager.data()->setValue(this->string, "comment");
    pointPropertyManager.data()->setValue(this->size, size);
    colorPropertyManager.data()->setValue(this->colour, colour);

}

CommentObject::~CommentObject(){
}

void CommentObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(colorPropertyManager->value(colour));

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

    painter->setFont(fontPropertyManager->value(font));
    painter->drawText(QRect(0, 0, pointPropertyManager->value(size).x(), pointPropertyManager->value(size).y()),
                      Qt::AlignCenter | Qt::TextWordWrap,
                      stringPropertyManager->value(string));
}

QtTreePropertyBrowser* CommentObject::getPropertyBrowser(){
    return propertyBrowser.data();
}

