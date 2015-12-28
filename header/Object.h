#ifndef OBJECT_H
#define OBJECT_H

#include "header/Connector.h"
#include "header/Element.h"

class Object : public Element
{

Q_OBJECT

private:

protected:

    QVector<Connector*> startPointConnectors;
    QVector<Connector*> endPointConnectors;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Object();
    virtual ~Object();
    virtual QtTreePropertyBrowser* getPropertyBrowser() = 0;

};

#endif // OBJECT_H
