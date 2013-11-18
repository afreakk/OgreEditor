#ifndef MENUMODE_H
#define MENUMODE_H
#include "Mode.h"
#include "MyPurplePanelColors.h"
#include <QFile>
#include <QJSEngine>
#include <QTextStream>
class MenuMode:public Mode
{
    public:
        MenuMode();
        virtual void update(const Ogre::FrameEvent&);
        virtual void init();
        virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);
        virtual bool keyPressed(const OIS::KeyEvent &keyEventRef);
        virtual bool mouseMoved(const OIS::MouseEvent &evt);
        virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    private:
        QJSEngine* initScript();
        void initTextColors(QJSEngine* engine);
        Ogre::ColourValue jsToColor(QJSValue jsArr);
        void _createDemoPanel();
        void switchHitbox();
        void removeCurrentBody();
        void checkForNewHitbox();
        bool readHitBoxOffset(Gui3D::PanelElement* e);
        float widgetDistance;
        Gui3D::Combobox* totalCombobox;
        Gui3D::Gui3D* mGui3D;
        Gorilla::Layer* mMousePointerLayer;
        Gorilla::Rectangle* mMousePointer;
        Ogre::Vector2 mNormalizedMousePosition;
        MyPurplePanelColors mMyPurplePanelColors;
        Ogre::ColourValue titleColor;
        Ogre::ColourValue textColor;

};
#endif /*MENUMODE_H*/
