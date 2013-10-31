#ifndef SOFTBODY_H
#define SOFTBODY_H
#include "object.h"
///Not implemented
class softbody:public Object
{
public:
    softbody();
    ~softbody();
    void makeBody(btScalar mass);
private:

};

#endif // SOFTBODY_H
