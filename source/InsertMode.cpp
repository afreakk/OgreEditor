#include "InsertMode.h"

InsertMode::InsertMode():modelDistance(0)
{
}
void InsertMode::init()
{    
//    rEngine->m_pCameraNode->setOrientation(Ogre::Quaternion::IDENTITY);
    rEngine->m_pCamera->setOrientation(Ogre::Quaternion::IDENTITY);
}

void InsertMode::update()
{
    rEngine->m_TranslateVector = Ogre::Vector3::ZERO;
    rEngine->getInput();
    rEngine->moveCamera();
    moveModel();
}
bool InsertMode::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    return true;
}
bool InsertMode::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    return true;
}
bool InsertMode::mouseMoved(const OIS::MouseEvent &evt)
{
    modelDistance = evt.state.Z.abs;
    rEngine->m_pLog->logMessage("wuuuuuuuuuuuuut");
    rEngine->mouseMoved(evt);
    return true;
}
bool InsertMode::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
}
bool InsertMode::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
}
void InsertMode::moveModel()
{
    if(currentNode)
    {
        Ogre::SceneNode* camNode = rEngine->m_pCameraNode;
        currentNode->setPosition(camNode->getPosition());
        currentNode->setOrientation(camNode->getOrientation());
        currentNode->translate(0.0f,0.0f,-modelDistance,Ogre::Node::TS_LOCAL);
    }
}
