#ifndef ELEMENT_H
#define ELEMENT_H

#include <QVector2D>

class Element
{
private:

    QVector2D position;

public:

    virtual void render() = 0;

};

#endif // ELEMENT_H
