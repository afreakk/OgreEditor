#include "world.h"

World::World(btScalar averageFPS,btScalar lowestFPS,btVector3 gravity):mWorld(NULL)
{
    initNormal(averageFPS,lowestFPS,gravity);
}
void World::stepDebug()
{
    mWorld->stepDebug();
}

void World::initNormal(btScalar averageFPS,btScalar lowestFPS,btVector3& gravity)
{
    mWorld = new worldsinglethread(averageFPS, lowestFPS);
    mWorld->init(gravity);
}

void World::step(btScalar timeStep)
{
    mWorld->step(timeStep);
}
RigidBody* World::addRigidBody(btScalar mass, Ogre::Entity* entity ,int shapeType, int group,int mask,btTransform offset)
{

    BtOgre::StaticMeshToShapeConverter converter(entity);
    btCollisionShape * mShape = Shapez::setupShape(shapeType,converter);
    btVector3 localInertia(0,0,0);
    mShape->calculateLocalInertia(mass,localInertia);
    Ogre::SceneNode *parentNode = entity->getParentSceneNode();
    BtOgre::RigidBodyState *state=NULL;
    if(offset==btTransform::getIdentity())
        state = new BtOgre::RigidBodyState(parentNode);
    else
        state = new BtOgre::RigidBodyState(parentNode,nodeToBullet(parentNode),offset);
    RigidBody* xBody = new RigidBody(mass,state,mShape,localInertia,group,mask);
    collisionShapes.push_back(mShape);
    return xBody;
}
btTransform World::nodeToBullet(Ogre::SceneNode* node)
{
    btVector3 pos = BtOgre::Convert::toBullet(node->getPosition() );
    btQuaternion rot = BtOgre::Convert::toBullet(node->getOrientation());
    btTransform trz; trz.setIdentity();
    trz.setOrigin(pos*2.0);
    trz.setRotation(rot);
    return trz;
}

ThirdPersonController* World::addThirdPersonController(int resolutionX, int resolutionY,Ogre::Entity* entity ,int shapeType,int group,int mask, btScalar contactProcessingTreshold
                                     ,Ogre::Vector3 posOffset, Ogre::Quaternion rotOffset)
{
    btTransform startTransform;
    startTransform.setIdentity ();
    Ogre::Node* cPrntNode = entity->getParentNode();
    const Ogre::Vector3& nodePos = cPrntNode->getPosition();
    const Ogre::Quaternion& nodeOrient = cPrntNode->getOrientation();

    startTransform.setOrigin (btVector3(nodePos.x, nodePos.y, nodePos.z));
    startTransform.setRotation(BtOgre::Convert::toBullet(nodeOrient));


    btPairCachingGhostObject* m_ghostObject = new btPairCachingGhostObject();
    m_ghostObject->setWorldTransform(startTransform);
    mWorld->getWorld()->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

    BtOgre::StaticMeshToShapeConverter converter(entity);
    btConvexShape * mShape = ConvexShapez::setupShape(shapeType,converter);
    btVector3 cScale = mShape->getLocalScaling();

    m_ghostObject->setCollisionShape (mShape);
    m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

    btScalar stepHeight = btScalar(0.35);
    btKinematicCharacterController* m_character = new btKinematicCharacterController (m_ghostObject,mShape,stepHeight);
    mWorld->getWorld()->addCollisionObject(m_ghostObject,group, mask);
    mWorld->getWorld()->addAction(m_character);
    ThirdPersonController* tpc = new ThirdPersonController(posOffset,rotOffset,m_character,m_ghostObject,cPrntNode,resolutionX
                                                           ,resolutionY,mWorld->getWorld());
    collisionShapes.push_back(mShape);
    return tpc;
}


RigidBody* World::addAnimatedRigidBody(btScalar mass, Ogre::Entity* entity ,int shapeType,int group,int mask, btScalar contactProcessingTreshold)
{
    BtOgre::AnimatedMeshToShapeConverter converter(entity);
    btCollisionShape * mShape = Shapez::setupShapeAnimated(shapeType,converter);
    btVector3 localInertia(0,0,0);
    mShape->calculateLocalInertia(mass,localInertia);
    RigidBodyStateAnimated *state = new RigidBodyStateAnimated(entity->getParentSceneNode());
    RigidBody* xBody = new RigidBody(mass,state,mShape,localInertia,group,mask);
    xBody->setActivationState(DISABLE_DEACTIVATION);
    state->setRigidBody(xBody,shapeType);
    state->setEntity(entity);
    if(contactProcessingTreshold != 0)
        xBody->setContactProcessingThreshold(contactProcessingTreshold);
    collisionShapes.push_back(mShape);
    return xBody;
}
RigidBody* World::addStaticRigidBody(Ogre::Entity* entity ,int shapeType,int group,int mask, btScalar contactProcessingTreshold)
{
    BtOgre::StaticMeshToShapeConverter converter(entity);
    btCollisionShape * mShape = Shapez::setupShape(shapeType,converter);
    btVector3 localInertia(0,0,0);
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(entity->getParentSceneNode());
    RigidBody* xBody = new RigidBody(0,state,mShape,localInertia,group,mask);
    if(contactProcessingTreshold != 0)
        xBody->setContactProcessingThreshold(contactProcessingTreshold);
    collisionShapes.push_back(mShape);
    return xBody;
}
RigidBody* World::addKinematicRigidBody(Ogre::Entity* entity ,int shapeType,int group,int mask, btScalar contactProcessingTreshold)
{
    BtOgre::StaticMeshToShapeConverter converter(entity);
    btCollisionShape * mShape = Shapez::setupShape(shapeType,converter);
    btVector3 localInertia(0,0,0);
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(entity->getParentSceneNode());
    RigidBody* xBody = new RigidBody(0,state,mShape,localInertia,group,mask);
    xBody->setCollisionFlags( xBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    xBody->setActivationState(DISABLE_DEACTIVATION);
    if(contactProcessingTreshold != 0)
        xBody->setContactProcessingThreshold(contactProcessingTreshold);
    collisionShapes.push_back(mShape);
    return xBody;
}
btPoint2PointConstraint* World::addPointToPointConstraint(btRigidBody& rbA,btRigidBody& rbB, const btVector3& pivotInA,const btVector3& pivotInB)
{
    btPoint2PointConstraint* constraint= new btPoint2PointConstraint(rbA,rbB,pivotInA,pivotInB);
    mWorld->getWorld()->addConstraint(constraint);
    return constraint;
}

void World::enableDebugging(Ogre::SceneNode* rootSceneNode)
{
    mWorld->enableDebugging(rootSceneNode);
}
btDiscreteDynamicsWorld* World::getWorld()
{
    return mWorld->getWorld();
}

World::~World()
{
    for (int i=getWorld()->getNumCollisionObjects()-1; i>=0 ;i--)
    {
        btCollisionObject* obj = getWorld()->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        btMotionState* motState = NULL;
        if(body&&body->getMotionState())
        {
            motState = body->getMotionState();
            delete motState;
            motState=NULL;
            body->setMotionState(NULL);
        }
        getWorld()->removeCollisionObject( obj );
        delete obj;
    }
    for(int i=0; i<collisionShapes.size(); i++)
        delete collisionShapes[i];
    collisionShapes.clear();
    delete mWorld;
}
