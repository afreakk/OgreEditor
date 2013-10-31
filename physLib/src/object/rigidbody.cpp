#include "rigidbody.h"

RigidBody::RigidBody(btScalar mass, btMotionState* motionState,btCollisionShape* collisionShape,btVector3&localInertia, int group, int mask)
    :btRigidBody(mass,motionState,collisionShape,localInertia),mtnState(motionState)
{
    mWorld->addRigidBody(this,group,mask);
}
RigidBody::~RigidBody()
{
    if(mtnState){
        if(this->getMotionState()){
            delete mtnState;mtnState=NULL;
        }
    }
    mWorld->removeRigidBody(this);
}
