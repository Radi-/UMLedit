#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtWidgets>
#include <QPoint>
#include <QGraphicsItem>
#include <QPainter>

class Element : public QGraphicsItem
{
private:

protected:

    QPoint size;
    QColor colour;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Element();
    virtual ~Element();

    virtual void setSize(QPoint size);
    void setColour(QColor colour);

    QRectF boundingRect() const override;

};

#endif // ELEMENT_H
