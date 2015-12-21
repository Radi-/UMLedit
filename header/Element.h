#ifndef ELEMENT_H
#define ELEMENT_H

#include <QPoint>
#include <QGraphicsItem>
#include <QPainter>

class Element : public QGraphicsItem
{
private:

protected:

    QPoint size;
    QColor colour;

public:

    Element();
    virtual ~Element();

    void setSize(QPoint size);
    void setColour(QColor colour);

    QRectF boundingRect() const override;

};

#endif // ELEMENT_H
