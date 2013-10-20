#ifndef INSERTMODE_H
#define INSERTMODE_H
#include "Mode.h"
class InsertMode:public Mode
{
    public:
        InsertMode();
        virtual void update(double);
        virtual void init();
        virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);
        virtual bool keyPressed(const OIS::KeyEvent &keyEventRef);
        virtual bool mouseMoved(const OIS::MouseEvent &evt);
        virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    private:
        bool rMode;
        bool sMode;
        void rotateModel(const OIS::MouseEvent &evt);
        void scaleModel(const OIS::MouseEvent &evt);

};
#endif /* INSERTMODE_H */
