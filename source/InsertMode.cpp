#include "InsertMode.h"

InsertMode::InsertMode()
{
}
void InsertMode::init()
{    
}
void InsertMode::update()
{
    moveModel();
}
bool InsertMode::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    return true;
}
bool InsertMode::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    return true;
}
bool InsertMode::mouseMoved(const OIS::MouseEvent &evt)
{
    rEngine->mFPC->mouseMoved(evt);
    zDistance += evt.state.Z.rel;
    return true;
}
bool InsertMode::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
    return true;
}
bool InsertMode::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}
