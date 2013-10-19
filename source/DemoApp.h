//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "OgreFramework.h"
#include "Gui3D.h"
#include "Gui3DPanel.h"
 
#include "MyPurplePanelColors.h"
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class DemoApp : public OIS::KeyListener, OIS::MouseListener
{
    struct modelInfo
    {
        Ogre::String name;
        Ogre::SceneNode* node;
    };
public:
	DemoApp();
	~DemoApp();
 
	void startDemo();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool iKeyPressed(const OIS::KeyEvent &keyEventRef);
	bool mKeyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
	bool mKeyReleased(const OIS::KeyEvent &keyEventRef);
	bool iKeyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool iMouseMoved(const OIS::MouseEvent &evt);
	bool mMouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool iMousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool mMousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool iMouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mMouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
private:
    void moveModel();
    bool hasEnding (std::string const &fullString, std::string const &ending);
    void _createDemoPanel();
    bool buttonPressed(Gui3D::PanelElement*);
    bool checkboxChecked(Gui3D::PanelElement*);
    bool addModel(Gui3D::Combobox* e);
    bool selectModel(Gui3D::Combobox* e);
    Gui3D::Combobox* addedCombobox;
    Gui3D::Combobox* totalCombobox;
    Gui3D::Panel* panel;
    float widgetDistance;
    float modelDistance;
    unsigned int modelsPlaced;
    Ogre::SceneNode * currentNode;
    Ogre::Vector2 getScreenCenterMouseDistance();
    OgreFramework* rEngine;
    void initGUI();
    void setupDemoScene();
	void runDemo();
	Ogre::SceneNode*			m_pOgreHeadNode;
	Ogre::Entity*				m_pOgreHeadEntity;
    std::vector<Ogre::String> totalModels;
    std::vector<Ogre::String> addedModels;
	bool					m_bShutdown;
    std::vector<Ogre::Entity*> entitys;
    // Gui3D main object
    Gui3D::Gui3D* mGui3D;
    Ogre::ResourceGroupManager* rGrpMgr; 
    // The main panel
    Gui3D::Panel* mPanel;
    std::vector<modelInfo> models;
    bool insertMode;
     
    // Keep track of some captions to modify their contents on callback
    Gui3D::Caption* captionButton;
    Gui3D::Caption* captionChecked;
    Gui3D::Caption* captionCombobox;
     
    int _widthPadding;
    int _width;
    int _height;
    int _distance;
    int _wP;
    int _boxHeight;
    // As Gui3D doesn't fully abstract Gorilla, you still have to deal with it. 
    // See http://www.valentinfrechaud.fr/Gui3DWiki/index.php/Gui3D_and_Gorilla for more infos.
    Gorilla::Layer* mMousePointerLayer;
    Gorilla::Rectangle* mMousePointer;
    Ogre::Vector2 mNormalizedMousePosition;
     
    // For the smooth movment when moving the mouse
    Ogre::Vector3 cameraDirection;
     
    // Keep track of number of click on the button
    int mClicksOnButton;
     
    // The panel color object
    MyPurplePanelColors mMyPurplePanelColors;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
