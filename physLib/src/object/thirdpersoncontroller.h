#ifndef THIRDPERSONCONTROLLER_H
#define THIRDPERSONCONTROLLER_H
#include <btBulletDynamicsCommon.h>
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "math.h"
#include "Ogre.h"
#include "BtOgrePG.h"
#include "CollisionFilter.h"
class ThirdPersonController
{
public:
    ThirdPersonController(Ogre::Vector3 pOffset, Ogre::Quaternion rOffset, btKinematicCharacterController* charController,
        btPairCachingGhostObject* ghostObj, Ogre::Node* prntNode, int resolX, int resolY,btDiscreteDynamicsWorld* world);
    void updateCamera(Ogre::Camera* mCamera,int mouseX, int mouseY);
    void updateCharacter(bool gLeft, bool gRight, bool gForward, bool gBackward, const btScalar& dt);
    void setOffsetPosition(const Ogre::Vector3& offset);
    void setOffsetRotation(const Ogre::Quaternion& offset);
    void setCameraCollisionLayer(int layer);
private:
    int camCollideLayer;
    Ogre::Vector3 cPosOffset;
    Ogre::Quaternion cRotOffset;
    btKinematicCharacterController* m_character;
    btPairCachingGhostObject* m_ghostObject;
    Ogre::Node* cPrntNode;
    btScalar cAngle;
    int resX;
    int resY;
    btDiscreteDynamicsWorld* mWorld;
};

#endif // THIRDPERSONCONTROLLER_H
