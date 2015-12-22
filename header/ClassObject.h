#ifndef CLASSOBJECT_H
#define CLASSOBJECT_H

#include <QString>

#include "header/Object.h"

class ClassObject : public Object
{
private:

    QString name;
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

public:

    ClassObject();
    ClassObject(QPoint size, QColor colour);
    ~ClassObject();

    void setSize(QPoint size) override;

    void updateDrawingParameters(); //should be called every time when name, attributes, methods, nameFont or textFont change

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // CLASSOBJECT_H
