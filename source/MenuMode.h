#ifndef MENUMODE_H
#define MENUMODE_H
#include "Mode.h"
#include "MyPurplePanelColors.h"
class MenuMode:public Mode
{
    public:
        MenuMode();
        virtual void update(double);
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
        Gorilla::Layer* mMousePointerLayer;
        Gorilla::Rectangle* mMousePointer;
        Ogre::Vector2 mNormalizedMousePosition;
        MyPurplePanelColors mMyPurplePanelColors;
};
#endif /*MENUMODE_H*/
