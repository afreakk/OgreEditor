#include "Editor.h"
Editor::Editor():rEngine(NULL),currentMode(NULL),insertMode(NULL),menuMode(NULL),world(NULL),INSERTMODE(false),input(NULL)
{
}
 
Editor::~Editor()
{
    delete rEngine;
}
 
void Editor::startDemo()
{
    new OgreFramework();
    rEngine = OgreFramework::getSingletonPtr()->initOgre(this, "Editor");
    input = OgreFramework::getSingletonPtr()->initOIS(this,this);
	rEngine->m_pLog->logMessage("Ogre initialized!");
	setupDemoScene();
}
 
void Editor::setupDemoScene()
{
    world = new World();
    insertMode = new InsertMode();
    menuMode = new MenuMode();
    currentMode = menuMode;
    currentMode->setWorld(world); //set world for the editor
    currentMode->setInput(input); 
    currentMode->init();
	rEngine->m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
 
	rEngine->m_pSceneMgr->createLight("Light")->setPosition(75,75,75);
    world->enableDebugging(rEngine->m_pSceneMgr->getRootSceneNode()); //enable drawing hitboxes
    rEngine->m_pRoot->renderOneFrame();
}
 
bool Editor::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool windowClosed = rEngine->m_pRenderWnd->isClosed();
	bool goOn = (!windowClosed && !input->isOgreToBeShutDown());
    if(rEngine->m_pRenderWnd->isActive())
    {
        input->m_pKeyboard->capture();
        input->m_pMouse->capture();
        currentMode->update(evt.timeSinceLastFrame);
        world->stepDebug();
        world->step(evt.timeSinceLastFrame);
    }
    return goOn;
}
 
bool Editor::frameEnded(const Ogre::FrameEvent& evt)
{
    rEngine->m_pRoot->renderOneFrame();
}
 
bool Editor::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    input->keyPressed(keyEventRef);
    if(input->m_pKeyboard->isKeyDown(OIS::KC_TAB))
    {
        INSERTMODE = !INSERTMODE;
        if(!INSERTMODE)
            currentMode = menuMode;
        else
            currentMode = insertMode;
        currentMode->init();
    }
    return currentMode->keyPressed(keyEventRef);
}

bool Editor::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return currentMode->keyReleased(keyEventRef);
}
bool Editor::mouseMoved(const OIS::MouseEvent &evt)
{
	return currentMode->mouseMoved(evt);
}
bool Editor::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
    return currentMode->mousePressed(evt,id);
}
bool Editor::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return currentMode->mouseReleased(evt,id);
}
 
