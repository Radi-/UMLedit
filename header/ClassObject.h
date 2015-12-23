#ifndef CLASSOBJECT_H
#define CLASSOBJECT_H

#include <QString>

#include "header/Object.h"
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"

class ClassObject : public Object
{

Q_OBJECT

private:

    QtTreePropertyBrowser* propertyBrowser;

    QtGroupPropertyManager* groupPropertyManager;
    QtStringPropertyManager* stringPropertyManager;
    QtFontPropertyManager* fontPropertyManager;

    QtProperty* classGroup;
    QtProperty* name;

    QVector<QString> attributes;
    QVector<QString> methods;

    QFont nameFont;
    QFont textFont;
    float paddingCoefficient;
    int namePadding;
    int textPadding;
    int separatorLine1Y;
    int separatorLine2Y;
    int bottomLineY;
    int edgeLineX;

public slots:
    void updateDrawingParameters(); //should be called every time when name, attributes, methods, nameFont or textFont change
    void pointPropertyUpdated(QtProperty* property, QPoint size);
    void stringPropertyUpdated(QtProperty* property, QString string);

public:

    ClassObject();
    ClassObject(QPoint size, QColor colour);
    ~ClassObject();

    QtTreePropertyBrowser* getPropertyBrowser() override;

    void setSize(QPoint size) override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // CLASSOBJECT_H
