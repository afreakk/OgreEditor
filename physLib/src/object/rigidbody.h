#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "object.h"
#include "CollisionFilter.h"
class RigidBody:public Object,public btRigidBody
{
public:
    ///this class inherits from btrigidbody, so you can use addforce, etc for moving objects
    RigidBody(btScalar mass, btMotionState* motionState,btCollisionShape* collisionShape,btVector3&localInertia, int group, int mask);
    ~RigidBody();

private:
    btMotionState* mtnState;

};

#endif // RIGIDBODY_H
