#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "header/Element.h"

class Connector : public Element
{

public:
    enum class Type{
        association,
        aggregation,
        composition,
        generalization,
        realization,
        dependency
    };

private:

    Type type;
    QPoint endPoint;

public:

    Connector();
    ~Connector();

    void setType(Type type);
    void setEndPoint(QPoint endPoint);
    QtTreePropertyBrowser* getPropertyBrowser() override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

#endif // CONNECTOR_H
