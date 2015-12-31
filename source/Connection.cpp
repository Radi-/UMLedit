
#include "header/Connection.h"

Connection::Connection(){
}

Connection::Connection(Connector* connector, QPointF connectionPoint){

    this->connector = connector;
    this->connectionPoint = connectionPoint;
}

Connection::~Connection(){
}
