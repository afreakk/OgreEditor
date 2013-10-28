#include "InsertMode.h"

InsertMode::InsertMode():rMode(false),sMode(false)
{
}
void InsertMode::init()
{    
}
void InsertMode::update(double timeSinceLastFrame)
{
    rEngine->mFPC->update(timeSinceLastFrame,rEngine->m_pKeyboard);
    moveModel();
}
bool once = true;
bool InsertMode::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(keyEventRef.key == OIS::KC_LSHIFT)
        rMode=true;
    if(keyEventRef.key == OIS::KC_SPACE)
        sMode=true;
    if(keyEventRef.key == OIS::KC_X)
        FileIO::writeToFile(modelContainer,"lvl.hnz");
    if(keyEventRef.key == OIS::KC_Z&&once)
    {
        FileIO::writeToFile( FileIO::readFile("lvl.hnz",rEngine->m_pSceneMgr) , "testOfLzlHnz.hnz");
        once = false; //loading the same file twice causes error because duplicate sceneNode names gets made also why would you want that
    }
    return true;
}
bool InsertMode::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    if(keyEventRef.key == OIS::KC_LSHIFT)
        rMode=false;
    if(keyEventRef.key == OIS::KC_SPACE)
        sMode=false;
    return true;
}
bool InsertMode::mouseMoved(const OIS::MouseEvent &evt)
{
    bool mod = false;
    if(currentModel)
    {
        if(rMode)
            rotateModel(evt);
        else if(sMode)
            scaleModel(evt);
        mod=sMode+rMode;
    }
    if(!mod)
        rEngine->mFPC->mouseMoved(evt);
    zDistance += evt.state.Z.rel;
    return true;
}
void InsertMode::scaleModel(const OIS::MouseEvent &evt)
{
    float xA = evt.state.X.abs;
    float yA = evt.state.Y.abs;
    float a = xA*yA;
    a /= 5000.0;
    Ogre::Vector3 scaleA = Ogre::Vector3(a,a,a);
    currentModel->scaleNode->setScale(scaleA);
}
void InsertMode::rotateModel(const OIS::MouseEvent &evt)
{
    float xA = evt.state.X.rel/100.0;
    float yA = evt.state.Y.rel/100.0;
    currentModel->rotationNode->pitch(Ogre::Radian(yA));
    currentModel->rotationNode->yaw(Ogre::Radian(xA));
}
bool InsertMode::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
    currentModel = NULL;
    return true;
}
bool InsertMode::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}
