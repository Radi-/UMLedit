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

protected:
    QPointer<QtTreePropertyBrowser> propertyBrowser;

    QScopedPointer<QtGroupPropertyManager> groupPropertyManager;
    QScopedPointer<QtColorPropertyManager> colorPropertyManager;

    QScopedPointer<QtSpinBoxFactory> spinBoxFactory;
    QScopedPointer<QtColorEditorFactory> colorFactory;

    QtProperty* elementGroup;
    QtProperty* colour;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

public:

    Element();
    virtual ~Element();

    virtual QtTreePropertyBrowser* getPropertyBrowser() = 0;
    void setColour(QColor colour);
    void setAlpha(unsigned int alpha);

};
#endif // ELEMENT_H
