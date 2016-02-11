#ifndef CLASSOBJECT_H
#define CLASSOBJECT_H

#include <QString>
#include <QScopedPointer>

#include "header/Object.h"

class ClassObject : public Object
{

Q_OBJECT

private:

    QScopedPointer<QtLineEditFactory> lineEditFactory;
    QScopedPointer<QtFontEditorFactory> fontFactory;

    QScopedPointer<QtStringPropertyManager> stringPropertyManager;
    QScopedPointer<QtFontPropertyManager> fontPropertyManager;

    QtProperty* fontGroup;
    QtProperty* classGroup;
    QtProperty* name;

    QVector<QString> attributes;
    QVector<QString> methods;

    QtProperty* nameFont;
    QtProperty* textFont;
    float paddingCoefficient;
    int namePadding;
    int textPadding;
    int separatorLine1Y;
    int separatorLine2Y;
    int bottomLineY;
    int edgeLineX;

protected slots:
    void updateDrawingParameters() override; //should be called every time when name, attributes, methods, nameFont or textFont change

public slots:
    //void pointPropertyUpdated(QtProperty* property, QPoint size);
    void stringPropertyUpdated(QtProperty* property, QString string);

public:

    ClassObject();
    ~ClassObject();

    QtTreePropertyBrowser* getPropertyBrowser() override;
    void setSize(QPoint size) override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // CLASSOBJECT_H
