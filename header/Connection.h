#ifndef CONNECTION_H
#define CONNECTION_H

#include "header/Connector.h"

class Connection
{
public:

    Connector* connector;
    QPointF connectionPoint;

    Connection();
    Connection(Connector* connector, QPointF connectionPoint);
    ~Connection();
};

#endif // CONNECTION_H
