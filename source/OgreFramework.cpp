#include "OgreFramework.h"
 
 
template<> OgreFramework* Ogre::Singleton<OgreFramework>::msSingleton = 0;
 
OgreFramework::OgreFramework():
	m_pRoot(0),
	m_pSceneMgr(0),
	m_pRenderWnd(0),
	m_pCamera(0),
	m_pViewport(0),
	m_pLog(0),
	m_pTimer(0),
    mFPC(NULL),
    logPath("OgreFiles/Ogre.log"),
    pluginsPath("OgreFiles/plugins.cfg"),
    ogreCfgPath("OgreFiles/ogre.cfg")
{
}

OgreFramework::~OgreFramework()
{
    if(m_pRoot)
        delete m_pRoot;
}

void OgreFramework::setupLog() 
{
	new Ogre::LogManager();
	m_pLog = Ogre::LogManager::getSingleton().createLog(logPath, true, true, false);
	m_pLog->setDebugOutputEnabled(true);
}
bool OgreFramework::setupRootAndWindow(Ogre::String wndTitle)
{
	m_pRoot = new Ogre::Root(pluginsPath,ogreCfgPath);
	if(!m_pRoot->showConfigDialog())
		return false;
	m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
    return true;
}

void OgreFramework::setupSceneMgrAndCamera()
{
	m_pSceneMgr = m_pRoot->createSceneManager("OctreeSceneManager", "SceneManager");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pCamera = m_pSceneMgr->createCamera("Camera");
	m_pCamera->setNearClipDistance(1);
    m_pCamera->setPosition(0.0f,0.0f,0.0f);

	m_pViewport = m_pRenderWnd->addViewport(m_pCamera);
	m_pViewport->setBackgroundColour(Ogre::ColourValue(0.8f, 0.7f, 0.6f, 1.0f));
 
	m_pCamera->setAspectRatio(Ogre::Real(m_pViewport->getActualWidth()) / Ogre::Real(m_pViewport->getActualHeight()));

	m_pViewport->setCamera(m_pCamera);

}

void OgreFramework::setupResources()
{
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
}
OgreFramework* OgreFramework::initOgre(Ogre::FrameListener* frameListener, Ogre::String wndTitle)
{
    setupLog();
    if(!setupRootAndWindow(wndTitle))
        return 0;
    setupSceneMgrAndCamera(); 
    mFPC = new FirstPersonNoClip(m_pCamera); 
    setupResources(); 
 
	m_pTimer = new Ogre::Timer();
	m_pTimer->reset();
 
	m_pRenderWnd->setActive(true);
    m_pRoot->addFrameListener(frameListener);
	return getSingletonPtr();
}

InputHandling* OgreFramework::initOIS(OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
    InputHandling* input = new InputHandling();
    input->initOIS(pKeyListener,pMouseListener,m_pRenderWnd,m_pCamera);
    return input;
}
