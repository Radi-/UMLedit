#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtWidgets>
#include <QPoint>
#include <QGraphicsObject>
#include <QPainter>
#include <QScopedPointer>

#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"

class Element : public QGraphicsObject
{

Q_OBJECT

private:

protected:
    QScopedPointer<QtTreePropertyBrowser> propertyBrowser;

    QScopedPointer<QtColorPropertyManager> colorPropertyManager;

    QtProperty* colour;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Element();
    virtual ~Element();

    virtual QtTreePropertyBrowser* getPropertyBrowser() = 0;
    void setColour(QColor colour);

};
#endif // ELEMENT_H
