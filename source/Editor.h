#ifndef EDITOR_H
#define EDITOR_H
 
#include "InsertMode.h"
#include "MenuMode.h"
#include "OgreFrameListener.h"
#include "InputHandling.h" 
class Editor : public OIS::KeyListener, OIS::MouseListener, Ogre::FrameListener
{
public:
	Editor();
	~Editor();
	void startDemo();
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool frameEnded(const Ogre::FrameEvent& evt);
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);
private:
    Mode* currentMode;
    Mode* insertMode;
    Mode* menuMode;
    OgreFramework* rEngine;
    InputHandling* input;
    bool INSERTMODE;
    World* world;

    void setupDemoScene();
};
 
#endif 
