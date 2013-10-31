#include "worldbase.h"

WorldBase::WorldBase(btScalar averageFPS,btScalar lowestFPS):avgFPS(btScalar(1.0)/averageFPS),
    maxSubSteps(static_cast<int>(ceil(averageFPS/lowestFPS))),broadphase(NULL),collisionConfiguration(NULL),dispatcher(NULL)
  ,solver(NULL),world(NULL),mDebugDrawer(NULL)
{

}
WorldBase::~WorldBase()
{
    if(world){
    delete world;world=NULL;
    }
    if(solver){
    delete solver;solver=NULL;
    }
    if(broadphase){
    delete broadphase;broadphase=NULL;
    }
    if(dispatcher){
    delete dispatcher;dispatcher=NULL;
    }
    if(collisionConfiguration){
    delete collisionConfiguration;collisionConfiguration=NULL;
    }
}

void WorldBase::enableDebugging(Ogre::SceneNode* rootSceneNode)
{
    if(!mDebugDrawer)
    {
        mDebugDrawer = new BtOgre::DebugDrawer(rootSceneNode, world);
        world->setDebugDrawer(mDebugDrawer);
    }
}
btDiscreteDynamicsWorld* WorldBase::getWorld()
{
    return world;
}

void WorldBase::step(btScalar timeStep)
{
    if(world)
        world->stepSimulation(timeStep,maxSubSteps,avgFPS);
}
void WorldBase::stepDebug()
{
    if(mDebugDrawer)
        mDebugDrawer->step();
}

