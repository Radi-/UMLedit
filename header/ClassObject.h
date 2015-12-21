#ifndef CLASSOBJECT_H
#define CLASSOBJECT_H

#include <QVector>
#include <QString>

#include "header/Element.h"

class ClassObject : public Element
{
private:

    QString name;
    QVector<QString> attributes;
    QVector<QString> methods;

    QFont nameFont;
    QFont textFont;

public:

    ClassObject();
    ClassObject(QPoint size, QColor colour);
    ~ClassObject();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // CLASSOBJECT_H
