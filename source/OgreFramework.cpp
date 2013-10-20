#include "OgreFramework.h"
 

using namespace Ogre; 
 
template<> OgreFramework* Ogre::Singleton<OgreFramework>::msSingleton = 0;
 
OgreFramework::OgreFramework()
{
	m_MoveSpeed			= 0.1f;
	m_RotateSpeed		        = 0.3f;
 
	m_bShutDownOgre		        = false;
	m_iNumScreenShots	        = 0;
 
	m_pRoot				= 0;
	m_pSceneMgr			= 0;
	m_pRenderWnd		        = 0;
	m_pCamera			= 0;
	m_pViewport			= 0;
	m_pLog				= 0;
	m_pTimer			= 0;
 
	m_pInputMgr			= 0;
	m_pKeyboard			= 0;
	m_pMouse			= 0;
 
        m_pTrayMgr                      = 0;
        m_FrameEvent                    = Ogre::FrameEvent();
}
bool OgreFramework::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	if(m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
			m_bShutDownOgre = true;
			return true;
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ))
	{
		m_pRenderWnd->writeContentsToTimestampedFile("BOF_Screenshot_", ".png");
		return true;
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_M))
	{
		static int mode = 0;
 
		if(mode == 2)
		{
			m_pCamera->setPolygonMode(PM_SOLID);
			mode = 0;
		}
		else if(mode == 0)
		{
			 m_pCamera->setPolygonMode(PM_WIREFRAME);
			 mode = 1;
		}
		else if(mode == 1)
		{
			m_pCamera->setPolygonMode(PM_POINTS);
			mode = 2;
		}
	}
	return true;
}
bool OgreFramework::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}
bool OgreFramework::mouseMoved(const OIS::MouseEvent &evt)
{
    
	m_pCameraNode->yaw(Degree(evt.state.X.rel * -0.1f),Ogre::Node::TS_LOCAL);
	m_pCameraNode->pitch(Degree(evt.state.Y.rel * -0.1f),Ogre::Node::TS_LOCAL);
 
	return true;
}

bool OgreFramework::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}
 
bool OgreFramework::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}
void OgreFramework::updateOgre(double timeSinceLastFrame)
{
	m_MoveScale = m_MoveSpeed   * (float)timeSinceLastFrame;
	m_RotScale  = m_RotateSpeed * (float)timeSinceLastFrame;
 
 
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
       // m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
}
void OgreFramework::moveCamera()
{
	if(m_pKeyboard->isKeyDown(OIS::KC_LSHIFT)) 
        m_pCameraNode->translate(m_TranslateVector,Ogre::Node::TS_LOCAL);
	else
        m_pCameraNode->translate(m_TranslateVector/10,Ogre::Node::TS_LOCAL);
}
void OgreFramework::getInput()
{
	if(m_pKeyboard->isKeyDown(OIS::KC_A))
		m_TranslateVector.x = -m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_D))
		m_TranslateVector.x = m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_W))
		m_TranslateVector.z = -m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_S))
		m_TranslateVector.z = m_MoveScale;
}
OgreFramework::~OgreFramework()
{
    if(m_pInputMgr) OIS::InputManager::destroyInputSystem(m_pInputMgr);
    if(m_pTrayMgr)  delete m_pTrayMgr;
    if(m_pRoot)     delete m_pRoot;
}

bool OgreFramework::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
 
	m_pRoot = new Ogre::Root("OgreFiles/plugins.cfg","OgreFiles/ogre.cfg","OgreFiles/Ogre.log");
 
	Ogre::LogManager* logMgr = new Ogre::LogManager();
 
	m_pLog = Ogre::LogManager::getSingleton().createLog("OgreFiles/Ogre.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);
	if(!m_pRoot->showConfigDialog())
		return false;
	m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
 
	m_pSceneMgr = m_pRoot->createSceneManager(ST_GENERIC, "SceneManager");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
 
	m_pCamera = m_pSceneMgr->createCamera("Camera");
	m_pCamera->setNearClipDistance(1);
 
    m_pCameraNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
    m_pCameraNode->attachObject(m_pCamera);

	m_pViewport = m_pRenderWnd->addViewport(m_pCamera);
	m_pViewport->setBackgroundColour(ColourValue(0.8f, 0.7f, 0.6f, 1.0f));
 
	m_pCamera->setAspectRatio(Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight()));
 

	m_pViewport->setCamera(m_pCamera);
 
	size_t hWnd = 0;
    OIS::ParamList paramList;
    m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);
 
	paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
/*#if defined OIS_LINUX_PLATFORM
    paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif*/
 
	m_pInputMgr = OIS::InputManager::createInputSystem(paramList);
 
        m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
	m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));
 
	m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
	m_pMouse->getMouseState().width	 = m_pRenderWnd->getWidth();
 
	if(pKeyListener == 0)
		m_pKeyboard->setEventCallback(this);
	else
		m_pKeyboard->setEventCallback(pKeyListener);
 
	if(pMouseListener == 0)
		m_pMouse->setEventCallback(this);
	else
		m_pMouse->setEventCallback(pMouseListener);
 
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
        cf.load("OgreFiles/resources.cfg");
 
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        int count = false;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            count = true;
        }
        if(count)
            groupNames.push_back(secName); 
    }
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
 
	m_pTimer = new Ogre::Timer();
	m_pTimer->reset();
 
/*    OgreBites::InputContext inputz;
    inputz.mAccelerometer= NULL;
    inputz.mKeyboard = NULL;
    inputz.mMouse = m_pMouse;
    inputz.mMultiTouch = NULL;
	m_pTrayMgr = new OgreBites::SdkTrayManager("TrayMgr", m_pRenderWnd, inputz, this);
        m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
        m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
        m_pTrayMgr->hideCursor();*/
 
	m_pRenderWnd->setActive(true);
	return true;
}
