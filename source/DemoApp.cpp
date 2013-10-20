#include "DemoApp.h"
DemoApp::DemoApp()
{
    rEngine = NULL;
    currentMode=NULL;
    insertMode=NULL;
    menuMode=NULL;
    INSERTMODE=false;
}
 

//|||||||||||||||||||||||||||||||||||||||||||||||
 
DemoApp::~DemoApp()
{
       delete rEngine;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
void DemoApp::startDemo()
{
    new OgreFramework();
    rEngine = OgreFramework::getSingletonPtr();
	if(!rEngine->initOgre("Editor", this, this))
		return;
 
	m_bShutdown = false;
 
	rEngine->m_pLog->logMessage("Editor initialized!");
 
	setupDemoScene();
	runDemo();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::setupDemoScene()
{
    insertMode = new InsertMode();
    menuMode = new MenuMode();
    currentMode = menuMode;
    currentMode->init();
    ///
	rEngine->m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
 
	rEngine->m_pSceneMgr->createLight("Light")->setPosition(75,75,75);
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::runDemo()
{
	rEngine->m_pLog->logMessage("Start main loop...");
 
	double timeSinceLastFrame = 0;
	double startTime = 0;
 
    rEngine->m_pRenderWnd->resetStatistics();
 
	while(!m_bShutdown && !rEngine->isOgreToBeShutDown()) 
	{
		if(rEngine->m_pRenderWnd->isClosed())m_bShutdown = true;
 
		Ogre::WindowEventUtilities::messagePump();
 
		if(rEngine->m_pRenderWnd->isActive())
		{
			startTime = rEngine->m_pTimer->getMillisecondsCPU();

			rEngine->m_pKeyboard->capture();
			rEngine->m_pMouse->capture();
 
			rEngine->updateOgre(timeSinceLastFrame);
            currentMode->update(timeSinceLastFrame);

			rEngine->m_pRoot->renderOneFrame();
			timeSinceLastFrame = rEngine->m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}
 
	rEngine->m_pLog->logMessage("Main loop quit");
	rEngine->m_pLog->logMessage("Shutdown OGRE...");
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool DemoApp::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    rEngine->keyPressed(keyEventRef);
    if(rEngine->m_pKeyboard->isKeyDown(OIS::KC_TAB))
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

bool DemoApp::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return currentMode->keyReleased(keyEventRef);
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

bool DemoApp::mouseMoved(const OIS::MouseEvent &evt)
{
	return currentMode->mouseMoved(evt);
}
bool DemoApp::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
    return currentMode->mousePressed(evt,id);
}
bool DemoApp::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return currentMode->mouseReleased(evt,id);
}
 
