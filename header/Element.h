#ifndef ELEMENT_H
#define ELEMENT_H

#include <QVector2D>
#include <QGraphicsItem>

class Element : public QGraphicsItem
{
private:

    QVector2D position;
    QColor colour;

public:

    void setPosition(QVector2D position);
    void setColour(QColor colour);

};

#endif // ELEMENT_H
