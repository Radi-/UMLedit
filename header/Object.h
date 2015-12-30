#ifndef OBJECT_H
#define OBJECT_H

#include "header/Connector.h"
#include "header/Element.h"

class Object : public Element
{

Q_OBJECT

private:

protected:

    QScopedPointer<QtPointPropertyManager> pointPropertyManager;

    QtProperty* sizep;
    QtProperty* size;

    QVector<Connector*> startPointConnectors;
    QVector<Connector*> endPointConnectors;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Object();
    virtual ~Object();
    virtual void setSize(QPoint size);
    virtual QtTreePropertyBrowser* getPropertyBrowser() = 0;

    QRectF boundingRect() const override;
};

#endif // OBJECT_H
