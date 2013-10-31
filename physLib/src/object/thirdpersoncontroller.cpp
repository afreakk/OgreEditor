#include "thirdpersoncontroller.h"

ThirdPersonController::ThirdPersonController
(Ogre::Vector3 pOffset, Ogre::Quaternion rOffset,btKinematicCharacterController* charController
 ,btPairCachingGhostObject* ghostObj, Ogre::Node* prntNode, int resolX, int resolY,btDiscreteDynamicsWorld* world)

    :camCollideLayer(CollisionLayer::DEFAULT),cPosOffset(pOffset),cRotOffset(rOffset),m_character(charController)
    ,m_ghostObject(ghostObj),cPrntNode(prntNode),cAngle(0.0),resX(resolX),resY(resolY),mWorld(world)
{
}
void ThirdPersonController::updateCharacter(bool gLeft, bool gRight, bool gForward, bool gBackward, const btScalar& dt)
{

    btVector3 forwardDir(sin(cAngle),0,cos(cAngle));


    btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
    btScalar walkVelocity = btScalar(1.1) * 40.0; // 4 km/h -> 1.1 m/s
    btScalar walkSpeed = walkVelocity * dt;
    btScalar rotateSpeed = dt*2.0;

    if (gLeft)
    {
        btMatrix3x3 orn = m_ghostObject->getWorldTransform().getBasis();
        orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),rotateSpeed));
        cAngle += rotateSpeed;
        m_ghostObject->getWorldTransform ().setBasis(orn);
    }

    if (gRight)
    {
        btMatrix3x3 orn = m_ghostObject->getWorldTransform().getBasis();
        orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0),-rotateSpeed));
        cAngle -= rotateSpeed;
        m_ghostObject->getWorldTransform ().setBasis(orn);
    }

    if (gForward)
        walkDirection += forwardDir;

    if (gBackward)
        walkDirection -= forwardDir;


    m_character->setWalkDirection(walkDirection*walkSpeed);

    const btVector3& ghostOrigin = m_ghostObject->getWorldTransform().getOrigin();
    const btQuaternion& ghostRotation = m_ghostObject->getWorldTransform().getRotation();
    cPrntNode->setPosition( BtOgre::Convert::toOgre(ghostOrigin)+cPosOffset );
    Ogre::Quaternion oQuat = BtOgre::Convert::toOgre(ghostRotation);
    cPrntNode->setOrientation(oQuat);
    cPrntNode->rotate(cRotOffset);
}
void ThirdPersonController::setCameraCollisionLayer(int layer)
{
    camCollideLayer = layer;
}

void ThirdPersonController::updateCamera(Ogre::Camera* mCamera,int mouseX, int mouseY)
{
    const float PI = 4.0*atan(1.0);
    float cDist = 100.0f;
    btTransform characterWorldTrans;
    characterWorldTrans = m_ghostObject->getWorldTransform();
    Ogre::Vector3 charOrigin = BtOgre::Convert::toOgre(characterWorldTrans.getOrigin());
    Ogre::Vector3 camPos = charOrigin;
    float mX = floor(static_cast<float>(mouseX));
    float mY = floor(static_cast<float>(mouseY));
    mX /=resX;
    mY/=resY;
    mX*= PI*2.0;
    mY*= PI*2.0;
    camPos.x+=sin(mX)*cDist;
    camPos.z+=cos(mX)*cDist;
    if(mY<PI*2.0&&mY>-PI*2.0)
        camPos.y+=mY*(cDist/PI);
    else if(mY<-PI*2.0)
        camPos.y+= (-PI*2.0)*(cDist/PI);
    else if(mY>PI*2.0)
        camPos.y+= (PI*2.0)*(cDist/PI);

    btSphereShape cameraSphere(0.2f);
    btTransform cameraFrom,cameraTo;
    cameraFrom.setIdentity();
    cameraFrom.setOrigin(characterWorldTrans.getOrigin());
    cameraTo.setIdentity();
    cameraTo.setOrigin(BtOgre::Convert::toBullet(camPos));
    btCollisionWorld::ClosestConvexResultCallback cb( characterWorldTrans.getOrigin(), cameraTo.getOrigin() );
    cb.m_collisionFilterMask = camCollideLayer;
    mWorld->convexSweepTest(&cameraSphere,cameraFrom,cameraTo,cb);
    if (cb.hasHit())
    {
        btVector3 bCamPos = BtOgre::Convert::toBullet(camPos);
        btScalar minFraction  = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
        bCamPos.setInterpolate3(cameraFrom.getOrigin(),cameraTo.getOrigin(),minFraction);
        camPos = BtOgre::Convert::toOgre(bCamPos);
    }
    mCamera->setPosition(camPos);
    mCamera->lookAt(charOrigin);
}
void ThirdPersonController::setOffsetPosition(const Ogre::Vector3& offset)
{
    cPosOffset = offset;
}

void ThirdPersonController::setOffsetRotation(const Ogre::Quaternion& offset)
{
    cRotOffset = offset;
}
