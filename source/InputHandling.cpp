#include "InputHandling.h"

InputHandling::InputHandling():
	m_pInputMgr(NULL),
	m_pKeyboard(NULL),
	m_pMouse(NULL),
    rMode(0),
	m_iNumScreenShots(0),
	m_bShutDownOgre(false),
    m_pCamera(NULL)
{
}
InputHandling::~InputHandling()
{
    if(m_pInputMgr) 
        OIS::InputManager::destroyInputSystem(m_pInputMgr);
}
bool InputHandling::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

bool InputHandling::mouseMoved(const OIS::MouseEvent &evt)
{
	return true;
}

bool InputHandling::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}
 
bool InputHandling::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

bool InputHandling::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    handleExit();
    return true;
}

void InputHandling::linuxNoStickyMouse(OIS::ParamList & paramList)
{
/*#if defined OIS_LINUX_PLATFORM
    paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif*/
}

#include <OgreCamera.h>
bool InputHandling::handleExit()
{
	if(m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
        m_bShutDownOgre = true;
        return true;
	}
    return false;
}

#include <OgreRenderWindow.h>
#include <OgreStringConverter.h>
bool InputHandling::initOIS(OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener, Ogre::RenderWindow* m_pRenderWnd, Ogre::Camera* camera)
{
    m_pCamera = camera;
	size_t hWnd = 0;
    OIS::ParamList paramList;
    m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);
 
	paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
    linuxNoStickyMouse(paramList); 
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
}
