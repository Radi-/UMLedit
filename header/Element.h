#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtWidgets>
#include <QPoint>
#include <QGraphicsObject>
#include <QPainter>
#include <QScopedPointer>

#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"

class Element : public QGraphicsObject
{

Q_OBJECT

private:

protected slots:
    virtual void updateDrawingParameters();
    virtual void pointPropertyUpdated(QtProperty* property, QPoint size);

protected:
    QScopedPointer<QtTreePropertyBrowser> propertyBrowser;

    QScopedPointer<QtGroupPropertyManager> groupPropertyManager;
    QScopedPointer<QtColorPropertyManager> colorPropertyManager;
    QScopedPointer<QtPointPropertyManager> pointPropertyManager;

    QScopedPointer<QtSpinBoxFactory> spinBoxFactory;
    QScopedPointer<QtColorEditorFactory> colorFactory;

    QtProperty* elementGroup;
    QtProperty* sizep;
    QtProperty* colour;
    QtProperty* size;

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
