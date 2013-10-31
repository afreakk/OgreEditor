#include "object.h"
btDiscreteDynamicsWorld* Object::mWorld=NULL;
Object::Object()
{

}
void Object::setWorld(btDiscreteDynamicsWorld* world)
{
    mWorld = world;
}

Object::~Object()
{

}
