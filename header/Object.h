#ifndef OBJECT_H
#define OBJECT_H

#include "header/Connector.h"
#include "header/Element.h"

class Object : public Element
{
private:

protected:

    QVector<Connector*> startPointConnectors;
    QVector<Connector*> endPointConnectors;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Object();
    virtual ~Object();

};

#endif // OBJECT_H
