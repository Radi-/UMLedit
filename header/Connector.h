#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "header/Element.h"

class Connector : public Element
{

Q_OBJECT

public:
    enum class Type{
        association,
        aggregation,
        composition,
        generalization,
        realization,
        dependency
    };

private slots:

    void checkGeometryChange();

signals:

    void endPointChanged();

private:

    Type type;
    QPointF endPoint;

    int boundingRectPadding; //arbitrary padding to all sides of the bounding rectangle to account for arrow head symbols

public:

    Connector();
    ~Connector();

    void setType(Type type);
    void setEndPoint(QPointF endPoint);
    QtTreePropertyBrowser* getPropertyBrowser() override;

    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;

};

#endif // CONNECTOR_H
