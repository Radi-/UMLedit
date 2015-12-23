#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtWidgets>
#include <QPoint>
#include <QGraphicsObject>
#include <QPainter>

#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"

class Element : public QGraphicsObject
{

Q_OBJECT

private:

protected:
    QtColorPropertyManager* colorPropertyManager;
    QtPointPropertyManager* pointPropertyManager;

    QtProperty* sizep;
    QtProperty* colourp;
    QtProperty* size;
    QColor colour;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Element();
    virtual ~Element();

    virtual QtTreePropertyBrowser* getPropertyBrowser() = 0;
    virtual void setSize(QPoint size);
    void setColour(QColor colour);

    QRectF boundingRect() const override;

};
#endif // ELEMENT_H
