#ifndef OBJECT_H
#define OBJECT_H

#include "header/Element.h"

class Object : public Element
{
private:


public:

    virtual void render() = 0;

};

#endif // OBJECT_H
