#include "worldsinglethread.h"


worldsinglethread::worldsinglethread(btScalar averageFPS,btScalar lowestFPS):WorldBase(averageFPS, lowestFPS)
{

}
void worldsinglethread::init(btVector3 & gravity)
{
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    world = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    world->setGravity(gravity);
    Object::setWorld(world);
}


worldsinglethread::~worldsinglethread()
{

}
