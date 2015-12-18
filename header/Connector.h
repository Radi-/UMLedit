#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "header/Element.h"

class Connector : public Element
{
private:

    QVector2D endPoint;

public:

    void render();

};

#endif // CONNECTOR_H
