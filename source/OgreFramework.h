//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_FRAMEWORK_H
#define OGRE_FRAMEWORK_H
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
 
#include <SdkTrays.h>
#include "FirstPersonNoClip.h" 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class OgreFramework : public Ogre::Singleton<OgreFramework>, OIS::KeyListener, OIS::MouseListener
{
public:
	OgreFramework();
	~OgreFramework();
 
	bool initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener = 0, OIS::MouseListener *pMouseListener = 0);
	void updateOgre(double timeSinceLastFrame);
 
	bool isOgreToBeShutDown()const{return m_bShutDownOgre;}
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
 
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
 
	Ogre::Root*				m_pRoot;
	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Viewport*				m_pViewport;
	Ogre::Log*				m_pLog;
	Ogre::Timer*				m_pTimer;
    FirstPersonNoClip*          mFPC;
 
	OIS::InputManager*			m_pInputMgr;
	OIS::Keyboard*				m_pKeyboard;
	OIS::Mouse*				m_pMouse;
    Ogre::FrameEvent                        m_FrameEvent;
    std::vector<Ogre::String> groupNames;
private:
	Ogre::Camera*				m_pCamera;
    Ogre::Quaternion            m_pCamQuat;
	OgreFramework(const OgreFramework&);
	OgreFramework& operator= (const OgreFramework&);
 
	OgreBites::SdkTrayManager*	        m_pTrayMgr;
	int					m_iNumScreenShots;
 
	bool					m_bShutDownOgre;
 
	Ogre::Real				m_MoveSpeed; 
	Ogre::Degree				m_RotateSpeed; 
	float					m_MoveScale; 
	Ogre::Degree				m_RotScale;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
