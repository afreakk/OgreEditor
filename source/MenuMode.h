#ifndef MENUMODE_H
#define MENUMODE_H
#include "Mode.h"
#include "MyPurplePanelColors.h"
class MenuMode:public Mode
{
    public:
        MenuMode();
        virtual void update();
        virtual void init();
        virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);
        virtual bool keyPressed(const OIS::KeyEvent &keyEventRef);
        virtual bool mouseMoved(const OIS::MouseEvent &evt);
        virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    private:
        Ogre::Vector2 getScreenCenterMouseDistance();
        void _createDemoPanel();
        float widgetDistance;
        Gui3D::Combobox* totalCombobox;
        Gui3D::Gui3D* mGui3D;
        Gui3D::Panel* mPanel;
        Gorilla::Layer* mMousePointerLayer;
        Gorilla::Rectangle* mMousePointer;
        Ogre::Vector2 mNormalizedMousePosition;
        // For the smooth movment when moving the mouse
        Ogre::Vector3 cameraDirection;
        // The panel color object
        MyPurplePanelColors mMyPurplePanelColors;
};
#endif /*MENUMODE_H*/
