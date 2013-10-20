//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_DEMO_H
#define OGRE_DEMO_H
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "InsertMode.h"
#include "MenuMode.h"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class DemoApp : public OIS::KeyListener, OIS::MouseListener
{
public:
	DemoApp();
	~DemoApp();
 
	void startDemo();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
private:
    Mode* currentMode;
    Mode* insertMode;
    Mode* menuMode;
    OgreFramework* rEngine;
    void setupDemoScene();
	void runDemo();
	bool m_bShutdown;
    bool INSERTMODE;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
