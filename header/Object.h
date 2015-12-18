#ifndef OBJECT_H
#define OBJECT_H

#include "header/Element.h"

class Object : public Element
{
private:


public:

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

};

#endif // OBJECT_H
