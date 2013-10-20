#ifndef FIRSTPERSONNOCLIP_H
#define FIRSTPERSONNOCLIP_H

#include <OISKeyboard.h>
#include <OISMouse.h>
#include "SdkCameraMan.h"
class FirstPersonNoClip
{
    public:
        FirstPersonNoClip(Ogre::Camera*);
        ~FirstPersonNoClip();
        bool mouseMoved(const OIS::MouseEvent& evt);
        const Ogre::Quaternion& getOrientation();
        void update(float timeSinceLastFrame, OIS::Keyboard* inputManager);
        const Ogre::Vector3&    getPosition();
        Ogre::Ray getCameraToViewportRay(Ogre::Real screenx, Ogre::Real screeny);
    private: 
        Ogre::Camera* mCam;
        OgreBites::SdkCameraMan* mCameraMan;
};

#endif /*FIRSTPERSONNOCLIP_H*/
