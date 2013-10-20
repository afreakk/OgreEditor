#include "MenuMode.h"
MenuMode::MenuMode()
{
    widgetDistance = 10.0f;
    totalCombobox=NULL;
    mGui3D=NULL;
    mMousePointerLayer=NULL;
    mMousePointer=NULL;

    Ogre::Viewport * _viewport= rEngine->m_pViewport;
    mGui3D = new Gui3D::Gui3D(&mMyPurplePanelColors);
	mGui3D->createScreen(_viewport, "purple", "mainScreen");
 
	// Create a layer for the mousePointer
	mNormalizedMousePosition = Ogre::Vector2(0.5, 0.5);
	mMousePointerLayer = mGui3D->getScreen("mainScreen")->createLayer();
	mMousePointer = mMousePointerLayer->createRectangle(_viewport->getActualWidth()/2, 
		_viewport->getActualHeight()/2, 12, 18);
	mMousePointer->background_image("mousepointer");
 
	_createDemoPanel();
    rEngine->m_pLog->logMessage("Menu initialized");
}
void MenuMode::update()
{
    panel->injectTime(rEngine->m_FrameEvent.timeSinceLastFrame);
}
void MenuMode::init()
{
    Ogre::SceneNode* panelNode = panel->mNode;
    panelNode->setPosition(rEngine->mFPC->getPosition());
    panelNode->setOrientation(rEngine->mFPC->getOrientation());
    panelNode->translate(0.0f,0.0f,-widgetDistance,Ogre::Node::TS_LOCAL);
}
bool MenuMode::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    panel->injectKeyPressed(keyEventRef);
    return true;
}
bool MenuMode::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	rEngine->keyReleased(keyEventRef);
    panel->injectKeyReleased(keyEventRef);
    return true;
}
bool MenuMode::mouseMoved(const OIS::MouseEvent &evt)
{
    	// Set the new camera smooth direction movement
	Ogre::Vector2 distance(getScreenCenterMouseDistance());
 
	// Raycast for the actual panel
	Ogre::Real xMove = static_cast<Ogre::Real>(evt.state.X.rel);
	Ogre::Real yMove = static_cast<Ogre::Real>(evt.state.Y.rel);
 
    
    Ogre::Viewport* mViewport = rEngine->m_pViewport;
	mNormalizedMousePosition.x += xMove / mViewport->getActualWidth();
	mNormalizedMousePosition.y += yMove / mViewport->getActualHeight();
 
	mNormalizedMousePosition.x = std::max<Ogre::Real>(mNormalizedMousePosition.x, 0);
	mNormalizedMousePosition.y = std::max<Ogre::Real>(mNormalizedMousePosition.y, 0);
	mNormalizedMousePosition.x = std::min<Ogre::Real>(mNormalizedMousePosition.x, 1);
	mNormalizedMousePosition.y = std::min<Ogre::Real>(mNormalizedMousePosition.y, 1);
 
	mMousePointer->position(mNormalizedMousePosition.x * mViewport->getActualWidth(), mNormalizedMousePosition.y * mViewport->getActualHeight());
 
	panel->injectMouseMoved(rEngine->mFPC->getCameraToViewportRay(mNormalizedMousePosition.x, mNormalizedMousePosition.y));
    return true;
}
bool MenuMode::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
    panel->injectMousePressed(evt,id);
    if(totalCombobox->getOvered())
        Mode::addModel(totalCombobox);
    else if(addedCombobox->getOvered())
        Mode::selectModel(addedCombobox);
    return true;
}
bool MenuMode::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    panel->injectMouseReleased(evt,id);
    return true;
}
Ogre::Vector2 MenuMode::getScreenCenterMouseDistance()
{
    Ogre::Viewport* mViewport = rEngine->m_pViewport;
	Ogre::Real posX = (mMousePointer->position().x - mViewport->getActualWidth()) 
		/ mViewport->getActualWidth();
	Ogre::Real posY = (mMousePointer->position().y - mViewport->getActualHeight()) 
		/ mViewport->getActualHeight();
 
	return Ogre::Vector2(posX + 0.5, posY + 0.5);
}
void MenuMode::_createDemoPanel()
{
    Ogre::ResourceGroupManager* rGrpMgr = Ogre::ResourceGroupManager::getSingletonPtr();
    Ogre::SceneManager* mSceneMgr = rEngine->m_pSceneMgr;
	panel = new Gui3D::Panel(mGui3D, mSceneMgr, Ogre::Vector2(_width, _height),_distance, "purple", "model_select_panel");
 
	panel->makeCaption(_widthPadding, 0, _wP, _boxHeight*0.2, "add Model");
 
    for(int i=0; i<rEngine->groupNames.size(); i++)
    {
        Ogre::FileInfoListPtr filesPtr = rGrpMgr->listResourceFileInfo( rEngine->groupNames[i] );
        Ogre::FileInfoList fileInfoList = *filesPtr.getPointer();
        for(int j=0; j<fileInfoList.size(); j++)
        {
            if(hasEnding(fileInfoList[j].filename,".mesh"))
            {
                totalModels.push_back(fileInfoList[j].basename);
            }
        }
    }

    totalCombobox = panel->makeCombobox(_widthPadding/2,_boxHeight*0.2,_wP,_boxHeight*0.8,totalModels,5);
	panel->makeCaption(_widthPadding/2, _boxHeight, _wP, _boxHeight*0.2, "added Models:");
    addedCombobox = panel->makeCombobox(_widthPadding/2,_boxHeight*1.2,_wP,_boxHeight*0.8,addedModels,5);
	captionCombobox = panel->makeCaption(_widthPadding/2, _boxHeight*2.0, _wP, _boxHeight*0.2, "select a model for placing");
 
	panel->mNode->setPosition(0, 2.1, -8);
}
