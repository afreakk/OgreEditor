#ifndef WORLD_H
#define WORLD_H
#include <btBulletDynamicsCommon.h>
#include <math.h>
#include "worldsinglethread.h"
#include <vector>
#include "rigidbody.h"
#include "softbody.h"
#include "rigidbodystateanimated.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "math.h"
#include "thirdpersoncontroller.h"
/*! \mainpage Hans-Ogre-Bullet-Connection
 *
 * \section intro_sec Introduction
 *
 * This library is for making bullet easier to use with ogre.
 *
 * \section usage_sec Usage
 *
 * To use this library, make a variable from the world class , then add objects using f.x addRigidBody(), \n
 * then place worldVariable->step() in your update loop, with globaltime as parameter. \n
 * Start by looking at \link World \endlink class.\n
 *
 */
class World
{
public:
    /// Constructor, average fps of the game and lowest, gravitational pull in btVector3, multiThread is not working
    World(btScalar averageFPS=60.0,btScalar lowestFPS=12.0, btVector3 gravity=btVector3(0.0,-10.0,0.0));
    ///connects a ogre entity and its node to bullet, and returns a rigidbody, for shapeType use Shapez::
    RigidBody* addRigidBody(btScalar mass, Ogre::Entity* entity ,int shapeType, int group=CollisionLayer::DEFAULT,int mask=CollisionLayer::DEFAULT|CollisionLayer::CHARACTER,btTransform offset=btTransform(btTransform::getIdentity()));
    ///connects a ogre entity and its node to bullet, and returns a rigidbody, for shapeType use Shapez::, the hitbox of this rigidbody will update per frame to match the ogre 3dmodel
    RigidBody* addAnimatedRigidBody(btScalar mass, Ogre::Entity* entity ,int shapeType,int group=CollisionLayer::DEFAULT,int mask=CollisionLayer::DEFAULT|CollisionLayer::CHARACTER, btScalar contactProcessingTreshold=0.0);
    ///connects a ogre entity and its node to bullet, and returns a rigidbody. And makes it not not be affected by physics, but other objects can collide with it depending on the CollisionLayer::
    RigidBody* addStaticRigidBody(Ogre::Entity* entity ,int shapeType,int group=CollisionLayer::DEFAULT,int mask=CollisionLayer::DEFAULT|CollisionLayer::CHARACTER, btScalar contactProcessingTreshold=0.0);
    ///makes to ogre entity a static kinematic object, (use if you are going to move the rigidbody after instantiation)
    RigidBody* addKinematicRigidBody(Ogre::Entity* entity ,int shapeType,int group=CollisionLayer::DEFAULT,int mask=CollisionLayer::DEFAULT|CollisionLayer::CHARACTER, btScalar contactProcessingTreshold=0.0);
    ///Adds a thirdperson controller to the Ogre entity, here you need to use a convex shape, so use ConvexShapez:: for shapeType
    ThirdPersonController* addThirdPersonController(int resolutionX, int resolutionY, Ogre::Entity* entity ,int shapeType
            ,int group=CollisionLayer::CHARACTER,int mask=CollisionLayer::DEFAULT, btScalar contactProcessingTreshold=0.0
            ,Ogre::Vector3 posOffset=Ogre::Vector3(0.0,0.0,0.0), Ogre::Quaternion rotOffset=Ogre::Quaternion(0.0,0.0,0.0,0.0));
    ///Adds a point to point constaint between rbA and rbB from pivotinA to pivotinB

    ///Bullet offers a lot of ways to add constaint, make a constaint using bulletlibrary (f.x btHingeConstaint)
    ///then use getWorld()->addConstraint( ** ) ; to add it to the world.
    ///
    btPoint2PointConstraint* addPointToPointConstraint(btRigidBody& rbA,btRigidBody& rbB, const btVector3& pivotInA,const btVector3& pivotInB);
    ///Enables debugging, to view the outlines of the hitboxes
    void enableDebugging(Ogre::SceneNode* rootSceneNode);
    ///steps the world, input globaltime
    void step(btScalar timeStep);
    ///steps the debug drawer, this needs to be stepped aswell every time you step your world, (if you are using debugging)
    void stepDebug();
    ///returns the bullet core world
    btDiscreteDynamicsWorld* getWorld();
    ~World();
private:
    void initNormal(btScalar averageFPS,btScalar lowestFPS,btVector3 &gravity);

    WorldBase * mWorld;
    std::vector<btCollisionShape*> collisionShapes;
    btTransform nodeToBullet(Ogre::SceneNode* node);
};

#endif // WORLD_H
