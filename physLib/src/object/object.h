#ifndef OBJECT_H
#define OBJECT_H
#include <btBulletDynamicsCommon.h>
#include "BtOgrePG.h"
#include "BtOgreGP.h"
class Object
{
public:
    Object();
    ~Object();
    static void setWorld(btDiscreteDynamicsWorld* world);
protected:
  //  btCollisionObject* body;
    static btDiscreteDynamicsWorld* mWorld;
};

#endif // OBJECT_H
