#ifndef WORLDBASE_H
#define WORLDBASE_H
#include <btBulletDynamicsCommon.h>
#include <math.h>
#include <OgreEntity.h>
#include "BtOgreExtras.h"

class WorldBase
{
public:
    WorldBase(btScalar averageFPS,btScalar lowestFPS);
    ~WorldBase();
    void step(btScalar timeStep);
    void stepDebug();
    virtual void init(btVector3 & gravity)=0;
    void enableDebugging(Ogre::SceneNode* rootSceneNode);
    btDiscreteDynamicsWorld* getWorld();
protected:
    btDiscreteDynamicsWorld* world;
    btScalar avgFPS;
    int maxSubSteps;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    BtOgre::DebugDrawer* mDebugDrawer;
};

#endif // WORLDBASE_H
