#include "FirstPersonNoClip.h"
FirstPersonNoClip::FirstPersonNoClip(Ogre::Camera* cam):mCam(cam),mCameraMan(new OgreBites::SdkCameraMan(cam))
{
}
FirstPersonNoClip::~FirstPersonNoClip()
{
    delete mCameraMan;
    mCameraMan= NULL;
}
void FirstPersonNoClip::update(const Ogre::FrameEvent& evt)
{
    mCameraMan->frameRenderingQueued(evt);
}
void FirstPersonNoClip::keyDown(const OIS::KeyEvent& evt)
{
    mCameraMan->injectKeyDown(evt);
}
void FirstPersonNoClip::keyUp(const OIS::KeyEvent& evt)
{
    mCameraMan->injectKeyUp(evt);
}
bool FirstPersonNoClip::mouseMoved(const OIS::MouseEvent& evt)
{
    mCameraMan->injectMouseMove(evt);
    return true;
}
const Ogre::Quaternion& FirstPersonNoClip::getOrientation()
{
    return mCam->getOrientation();
}
const Ogre::Vector3&    FirstPersonNoClip::getPosition()
{
    return mCam->getPosition();
}
Ogre::Ray FirstPersonNoClip::getCameraToViewportRay(Ogre::Real screenx, Ogre::Real screeny)
{
    return mCam->getCameraToViewportRay(screenx,screeny);
}
OgreBites::SdkCameraMan* FirstPersonNoClip::getCameraMan()
{
    return mCameraMan;
}
