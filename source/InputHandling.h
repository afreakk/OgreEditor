#ifndef INPUTHANDLING_H
#define INPUTHANDLING_H

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
//forward declaration
namespace Ogre
{
    class RenderWindow;
    class Camera;
}
class InputHandling : public OIS::KeyListener, OIS::MouseListener 
{
public:
    InputHandling();
    ~InputHandling();
    bool initOIS(OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener, Ogre::RenderWindow* m_pRenderWnd, Ogre::Camera* camera);
	bool isOgreToBeShutDown(){return m_bShutDownOgre;}
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
	OIS::InputManager* m_pInputMgr;
	OIS::Keyboard* m_pKeyboard;
    OIS::Mouse* m_pMouse;
private:
    bool handleExit();
	bool m_bShutDownOgre;
    int rMode;
	int m_iNumScreenShots;
    Ogre::Camera* m_pCamera;
    void linuxNoStickyMouse(OIS::ParamList & paramList);
};
#endif 
