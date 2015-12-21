#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "header/Element.h"

class Connector : public Element
{
private:

    QPoint endPoint;

public:

    Connector();
    ~Connector();

    void setEndPoint(QPoint endPoint);

    QPainterPath shape() const override;

};

#endif // CONNECTOR_H
