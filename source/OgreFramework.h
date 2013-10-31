#ifndef OGREFRAMEWORK_H
#define OGREFRAMEWORK_H
 
#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include "FirstPersonNoClip.h" 
#include "InputHandling.h"
 
class OgreFramework : public Ogre::Singleton<OgreFramework>
{
public:
	OgreFramework();
	~OgreFramework();
 
	OgreFramework* initOgre(Ogre::FrameListener* frameListener, Ogre::String wndTitle);
    InputHandling* initOIS(OIS::KeyListener *pKeyListener = 0, OIS::MouseListener *pMouseListener = 0);
	void updateOgre(double timeSinceLastFrame);
 
	Ogre::Root*				    m_pRoot;
	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Viewport*				m_pViewport;
	Ogre::Log*				    m_pLog;
	Ogre::Timer*				m_pTimer;
    FirstPersonNoClip*          mFPC;
    //folder or groupnames , used by editor to fill model lists 
    std::vector<Ogre::String>   groupNames;
private:
	Ogre::Camera*               m_pCamera;
    void setupLog(); 
    bool setupRootAndWindow(Ogre::String wndTitle);
    void setupSceneMgrAndCamera();
    void setupResources();

    std::string logPath;
    std::string pluginsPath;
    std::string ogreCfgPath;
};
 
#endif 
