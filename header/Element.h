#ifndef ELEMENT_H
#define ELEMENT_H

#include <QVector2D>
#include <QGraphicsItem>
#include <QPainter>

class Element : public QGraphicsItem
{
private:

protected:

    QVector2D position;
    QColor colour;

public:

    void setPosition(QVector2D position);
    void setColour(QColor colour);

};

#endif // ELEMENT_H
