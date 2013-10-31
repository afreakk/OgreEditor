#ifndef RIGIDBODYSTATEANIMATED_H
#define RIGIDBODYSTATEANIMATED_H

#include "Shape.h"
class RigidBodyStateAnimated:public BtOgre::RigidBodyState
{
private:
    btRigidBody* body;
    Ogre::Entity* entity;
    int whatShape;
public:
    RigidBodyStateAnimated(Ogre::SceneNode *node, const btTransform &transform, const btTransform &offset = btTransform::getIdentity())
        : BtOgre::RigidBodyState(node,transform,offset),body(NULL),entity(NULL)
    {
    }

    RigidBodyStateAnimated(Ogre::SceneNode *node)
        : BtOgre::RigidBodyState(node),body(NULL),entity(NULL)
    {
    }
    void setRigidBody(btRigidBody* bodyInThis,int wtShape)
    {
        whatShape = wtShape;
        body = bodyInThis;
    }
    void setEntity(Ogre::Entity* entityInThis)
    {
        entity = entityInThis;
    }

    virtual void getWorldTransform(btTransform &ret) const
    {

        ret = mTransform;
    }

    virtual void setWorldTransform(const btTransform &in)
    {
        if (mNode == NULL)
            return;
        if(body&&entity)
        {
            BtOgre::AnimatedMeshToShapeConverter converter(entity);         //lol
            if(body->getCollisionShape())
                delete body->getCollisionShape();
            body->setCollisionShape(Shapez::setupShapeAnimated(whatShape,converter));
        }
        mTransform = in;
        btTransform transform = in * mCenterOfMassOffset;

        btQuaternion rot = transform.getRotation();
        btVector3 pos = transform.getOrigin();
        mNode->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
        mNode->setPosition(pos.x(), pos.y(), pos.z());
    }

};

#endif // RIGIDBODYSTATEANIMATED_H
