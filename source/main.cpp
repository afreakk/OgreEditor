/*#include "Ogre.h"
int main(void)
{

    Ogre::Root* _root = new Ogre::Root("OgreFiles/plugins.cfg", "OgreFiles/ogre.cfg", "OgreFiles/Ogre.log");
    if(!_root->showConfigDialog())
        return 444;
    Ogre::RenderWindow* _window = _root->initialise(true, "hEditor");
    Ogre::SceneManager* _sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC);
    Ogre::Camera* _camera = _sceneMgr->createCamera("Camera");
    _camera->setNearClipDistance(1.0f);
    Ogre::Viewport* _viewPort = _window->addViewport(_camera);
    _viewPort->setBackgroundColour(Ogre::ColourValue(0.0f,0.0f,0.0f));
    _camera->setAspectRatio(Ogre::Real(_viewPort->getActualWidth())/Ogre::Real(_viewPort->getActualHeight()));
    
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("OgreFiles/media/models/", "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    Ogre::Entity* ent = _sceneMgr->createEntity("ogrehead.mesh");
    _sceneMgr->getRootSceneNode()->attachObject(ent);

    _camera->setPosition(10.0f,0.0f,10.0f);
    _camera->lookAt(_sceneMgr->getRootSceneNode()->getPosition());

    Ogre::ConfigFile _resourceFile;
    _resourceFile.load("OgreFiles/resources.cfg");
    Ogre::ConfigFile::SectionIterator _secitr = _resourceFile.getSectionIterator();
    Ogre::ResourceGroupManager& _resourceGroupMgr = Ogre::ResourceGroupManager::getSingleton();
    while(_secitr.hasMoreElements())
    {
        Ogre::String _sectionName, _typeName, _dataName;

        _sectionName = _secitr.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* _settings = _secitr.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for(i=_settings->begin(); i!= _settings->end(); ++i)
        {
            _typeName = i->first;
            _dataName = i->second;
            _resourceGroupMgr.addResourceLocation(_dataName,_typeName,_sectionName);
        }
    }
    _resourceGroupMgr.initialiseAllResourceGroups();
    
    Ogre::SceneNode& _rSceneNode = *_sceneMgr.getRootSceneNode();
    Ogre::Entity* _ent = _sceneMgr.createEntity("robot.mesh");
    Ogre::SceneNode& _node1 = *_rSceneNode.createChildSceneNode();
    _node1.attachObject(_ent);
    while(true)
    _root->startRendering();
    //delete _ent;
    return 0;
}*/
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "DemoApp.h"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	try
      {
		DemoApp demo;
		demo.startDemo();
      }
	catch(std::exception& e)
      {
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occurred: %s\n", e.what());
#endif
      }
 
    return 0;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
