#include "DemoApp.h"
DemoApp::DemoApp()
{
    rEngine = NULL;
	m_pOgreHeadNode		= 0;
	m_pOgreHeadEntity		= 0;
    modelsPlaced=0;
    addedCombobox=NULL;
    insertMode=false;
    currentNode=NULL;
    widgetDistance= 10.0f;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
DemoApp::~DemoApp()
{
       delete rEngine;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
void DemoApp::initGUI()
{
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
    Ogre::Camera* mCamera = rEngine->m_pCamera;
    Ogre::SceneNode *mCameraNode = rEngine->m_pCameraNode;
	mCameraNode->setPosition(0, 2, 1);
	cameraDirection = Ogre::Vector3(0, 0, -1);
	mCameraNode->setDirection(cameraDirection);
}
Ogre::Vector2 DemoApp::getScreenCenterMouseDistance()
{
    Ogre::Viewport* mViewport = rEngine->m_pViewport;
	Ogre::Real posX = (mMousePointer->position().x - mViewport->getActualWidth()) 
		/ mViewport->getActualWidth();
	Ogre::Real posY = (mMousePointer->position().y - mViewport->getActualHeight()) 
		/ mViewport->getActualHeight();
 
	return Ogre::Vector2(posX + 0.5, posY + 0.5);
}
void DemoApp::startDemo()
{
    rEngine=new OgreFramework();
	if(!rEngine->initOgre("DemoApp v1.0", this, this))
		return;
 
	m_bShutdown = false;
 
	rEngine->m_pLog->logMessage("Demo initialized!");
 
	setupDemoScene();
	runDemo();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::setupDemoScene()
{
    initGUI();
    ///
	rEngine->m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
 
	rEngine->m_pSceneMgr->createLight("Light")->setPosition(75,75,75);
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::runDemo()
{
	rEngine->m_pLog->logMessage("Start main loop...");
 
	double timeSinceLastFrame = 0;
	double startTime = 0;
 
      rEngine->m_pRenderWnd->resetStatistics();
 
	while(!m_bShutdown && !rEngine->isOgreToBeShutDown()) 
	{
		if(rEngine->m_pRenderWnd->isClosed())m_bShutdown = true;
 
		Ogre::WindowEventUtilities::messagePump();
 
		if(rEngine->m_pRenderWnd->isActive())
		{
			startTime = rEngine->m_pTimer->getMillisecondsCPU();
 
			rEngine->m_pKeyboard->capture();
			rEngine->m_pMouse->capture();
 
			rEngine->updateOgre(timeSinceLastFrame);
			rEngine->m_pRoot->renderOneFrame();
			timeSinceLastFrame = rEngine->m_pTimer->getMillisecondsCPU() - startTime;
            if(insertMode)
            {
                rEngine->m_TranslateVector = Ogre::Vector3::ZERO;
                rEngine->getInput();
                rEngine->moveCamera();
                moveModel();
            }
            else
            {
                mPanel->injectTime(rEngine->m_FrameEvent.timeSinceLastFrame);
            }

		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}
 
	rEngine->m_pLog->logMessage("Main loop quit");
	rEngine->m_pLog->logMessage("Shutdown OGRE...");
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool DemoApp::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	rEngine->keyPressed(keyEventRef);

    mPanel->injectKeyPressed(keyEventRef);

	if(rEngine->m_pKeyboard->isKeyDown(OIS::KC_TAB))
	{
		 insertMode = !insertMode;
         if(!insertMode)
         {
            Ogre::SceneNode* camNode = rEngine->m_pCameraNode;
            Ogre::SceneNode* panelNode = panel->mNode;
            panelNode->setPosition(camNode->getPosition());
            panelNode->translate(0.0f,0.0f,-widgetDistance,Ogre::Node::TS_LOCAL);
            rEngine->m_pCameraNode->setOrientation(Ogre::Quaternion::IDENTITY);
            rEngine->m_pCamera->setOrientation(Ogre::Quaternion::IDENTITY);
         }
         else
         {
             rEngine->m_pCameraNode->setOrientation(Ogre::Quaternion::IDENTITY);
             rEngine->m_pCamera->setOrientation(Ogre::Quaternion::IDENTITY);
         }
	}
 
	return true;
}

bool DemoApp::iKeyPressed(const OIS::KeyEvent &keyEventRef)
{
}
bool DemoApp::mKeyPressed(const OIS::KeyEvent &keyEventRef)
{
}
bool DemoApp::mKeyReleased(const OIS::KeyEvent &keyEventRef)
{
	rEngine->keyReleased(keyEventRef);
    mPanel->injectKeyReleased(keyEventRef);
}
bool DemoApp::iKeyReleased(const OIS::KeyEvent &keyEventRef)
{
}
bool DemoApp::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    if(!insertMode)
        mKeyReleased(keyEventRef);
    else
        iKeyReleased(keyEventRef);
	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
bool DemoApp::iMouseMoved(const OIS::MouseEvent &evt)
{
    modelDistance = evt.state.Z.abs;
    rEngine->mouseMoved(evt);
}
bool DemoApp::mMouseMoved(const OIS::MouseEvent &evt)
{
    	// Set the new camera smooth direction movement
	Ogre::Vector2 distance(getScreenCenterMouseDistance());
    Ogre::Camera * mCamera = rEngine->m_pCamera;
	mCamera->setDirection(cameraDirection
		+ Ogre::Vector3(distance.x, -distance.y, 0) / 30);
 
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
 
	mMousePointer->position(
		mNormalizedMousePosition.x * mViewport->getActualWidth(), 
		mNormalizedMousePosition.y * mViewport->getActualHeight());
 
	mPanel->injectMouseMoved(mCamera->getCameraToViewportRay(
		mNormalizedMousePosition.x, mNormalizedMousePosition.y));
}
bool DemoApp::iMousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
}
bool DemoApp::mMousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
    mPanel->injectMousePressed(evt,id);
    Ogre::Vector2 currMousePos = mMousePointer->position();
    if(totalCombobox->getOvered())
        addModel(totalCombobox);
    else if(addedCombobox->getOvered())
        selectModel(addedCombobox);

}
bool DemoApp::iMouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
}
bool DemoApp::mMouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    mPanel->injectMouseReleased(evt,id);
}
bool DemoApp::mouseMoved(const OIS::MouseEvent &evt)
{
    if(!insertMode)
        mMouseMoved(evt);
    else
        iMouseMoved(evt);
	return true;
}
void DemoApp::moveModel()
{
    Ogre::SceneNode* camNode = rEngine->m_pCameraNode;
    currentNode->setPosition(camNode->getPosition());
    currentNode->setOrientation(camNode->getOrientation());
    currentNode->translate(0.0f,0.0f,-modelDistance,Ogre::Node::TS_LOCAL);
}
bool DemoApp::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
{
    if(!insertMode)
        mMousePressed(evt,id);
    else
        iMousePressed(evt,id);
    return true;
}
bool DemoApp::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(!insertMode)
        mMouseReleased(evt,id);
    else
        iMouseReleased(evt,id);
    return true;
}
bool DemoApp::hasEnding (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
void DemoApp::_createDemoPanel()
{
    _widthPadding = 20;
    _width = 400;
    _height = 400;
    _distance = 100;
    _wP = _width-_widthPadding;
    _boxHeight = _width/2;
    rGrpMgr = Ogre::ResourceGroupManager::getSingletonPtr();
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
 
	mPanel = panel;
	mPanel->mNode->setPosition(0, 2.1, -8);
}
 
bool DemoApp::selectModel(Gui3D::Combobox* e)
{
    Ogre::String _name = e->getValue();
    for(int i=0; i<models.size(); i++)
    {
        if(_name == models[i].name)
        {
            currentNode = models[i].node;
        }
    }
}
bool DemoApp::addModel(Gui3D::Combobox* e)
{
	Gui3D::Combobox* c =  e;
    modelInfo temp;
    Ogre::String modelName = c->getValue();
    modelsPlaced++;
    temp.node = rEngine->m_pSceneMgr->getRootSceneNode()->createChildSceneNode("node="+modelsPlaced);
    
    std::ostringstream x;
    x << modelsPlaced <<"/"<<modelName;
    Ogre::Entity* tempEnt = rEngine->m_pSceneMgr->createEntity(x.str(),modelName);
    temp.node->attachObject(tempEnt);
    temp.name = x.str();
    models.push_back(temp);
    entitys.push_back(tempEnt);
    std::ostringstream s;
    s << "Selected: " << x.str();
    captionCombobox->text(s.str());
    addedModels.push_back(temp.name);
    if(addedCombobox)
        panel->destroyCombobox(addedCombobox);
    delete addedCombobox;
    addedCombobox = panel->makeCombobox(_widthPadding/2,_boxHeight*1.2,_wP,_boxHeight*0.8,addedModels,5);
    addedCombobox->setCurrentValue(temp.name);
    addedCombobox->highlight();
    selectModel(addedCombobox);
	return true;
}
