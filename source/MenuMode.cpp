#include "MenuMode.h"
MenuMode::MenuMode()
{
    QJSEngine* engine = initScript();
    initTextColors(engine);
    delete engine;
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
void MenuMode::update(const Ogre::FrameEvent& evt)
{
    panel->injectTime(evt.timeSinceLastFrame);
    checkForNewHitbox();
}
void MenuMode::init()
{
    panel->getGUILayer()->show();
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
	input->keyReleased(keyEventRef);
    panel->injectKeyReleased(keyEventRef);
    return true;
}
bool MenuMode::mouseMoved(const OIS::MouseEvent &evt)
{
 
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
    if(mNormalizedMousePosition.x<0.6)
    {
        if(totalCombobox->getOvered())
        {
            Mode::addModel(totalCombobox->getValue());
            currentModel = NULL;
            setCaptionText(noneSelected);
        }
        else if(addedCombobox->getOvered())
            Mode::selectModel(addedCombobox);
    }
    return true;
}
void MenuMode::checkForNewHitbox()
{
    if(currentModel)
    {
        if(shapeTypeSelector->getValue() != currentModel->hitboxShapeType)
        {
            switchHitbox();
        }
    }
}
void MenuMode::switchHitbox()
{
    removeCurrentBody();
    currentModel->hitboxShapeType = shapeTypeSelector->getValue();
    int shapeType = hitboxSelection(currentModel->hitboxShapeType);
    currentModel->rigidBody = world->addRigidBody(0,currentModel->entity,shapeType);
}
void MenuMode::removeCurrentBody()
{
    btCollisionShape* currentShape = currentModel->rigidBody->getCollisionShape();
    world->getWorld()->removeCollisionObject(currentModel->rigidBody);
    delete currentModel->rigidBody;
    delete currentShape;
}
bool MenuMode::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    panel->injectMouseReleased(evt,id);
    return true;
}
void MenuMode::_createDemoPanel()
{
    Ogre::ResourceGroupManager* rGrpMgr = Ogre::ResourceGroupManager::getSingletonPtr();
    Ogre::SceneManager* mSceneMgr = rEngine->m_pSceneMgr;
	panel = new Gui3D::Panel(mGui3D, mSceneMgr, Ogre::Vector2(_width, _height),_distance, "purple", "model_select_panel");
 
	Gui3D::Caption* temp = panel->makeCaption(_widthPadding, 0, _wP, _boxHeight*0.2, "add Model");
    temp->textColor(titleColor);

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
    std::vector<std::string> collisionTypes;
    collisionTypes.push_back("Sphere");
    collisionTypes.push_back("Box");
    collisionTypes.push_back("Trimesh");
    collisionTypes.push_back("Cylinder");
    collisionTypes.push_back("Convex");
    collisionTypes.push_back("Capsule");
    totalCombobox =     panel->makeCombobox(_widthPadding/2,_boxHeight*0.2,_wP,_boxHeight*0.8,totalModels,5);
    temp =  panel->makeCaption(_widthPadding/2, _boxHeight*1.0, _wP, _boxHeight*0.2, "added Models:");
    addedCombobox =     panel->makeCombobox(_widthPadding/2,_boxHeight*1.2,_wP,_boxHeight*0.8,addedModels,5);
	captionCombobox =   panel->makeCaption(_widthPadding/2, _boxHeight*2.0, _wP, _boxHeight*0.2, noneSelected);
    shapeTypeSelector=  panel->makeInlineSelector(_widthPadding/2, _boxHeight*2.2, _wP, _boxHeight*0.2,collisionTypes);
    captionCombobox->textColor(titleColor);
    temp->textColor(titleColor);

    for(int i=0; i<3; i++)
    {
        hitBoxTranslationZone[i]    = panel->makeTextZone(_widthPadding/2+(_wP/8.0)*i, _boxHeight*2.75,_wP/8.0,_boxHeight*0.15,"0");
        hitBoxRotationZone[i]       = panel->makeTextZone(_widthPadding/2+(_wP/8.0)*i+(_wP/8.0)*5.0, _boxHeight*2.75,_wP/8.0,_boxHeight*0.15,"0");
        hitBoxScaleZone[i]          = panel->makeTextZone(_widthPadding/2+(_wP/8.0)*(i+0.5)+(_wP/4.0), _boxHeight*2.9, _wP/8.0, _boxHeight*0.15, "0");

        hitBoxTranslationZone[i]->setValueChangedCallback(this,&MenuMode::readHitBoxOffset);
        hitBoxRotationZone[i]->setValueChangedCallback(this,&MenuMode::readHitBoxOffset);
        hitBoxScaleZone[i]->setValueChangedCallback(this,&MenuMode::readHitBoxOffset);
    }
    temp = panel->makeCaption(_widthPadding/2+(_wP/8.0)*2.5, _boxHeight*2.4, _wP, _boxHeight*0.2, "HitBox/Mesh Offset:");
    temp->textColor(titleColor);
    temp = panel->makeCaption(_widthPadding/2, _boxHeight*2.55, _wP, _boxHeight*0.2, "Translation");
    temp->textColor(textColor);
    temp = panel->makeCaption(_widthPadding/2+(_wP/8.0)*5.0, _boxHeight*2.55, _wP, _boxHeight*0.2, "Rotation");
    temp->textColor(textColor);
    temp = panel->makeCaption(_widthPadding/2+(_wP/8.0)*(0.5)+(_wP/4.0),_boxHeight*3.05, _wP/4.0, _boxHeight*0.15, "Scale");
    temp->textColor(textColor);
 
	panel->mNode->setPosition(0, 2.1, -8);
}
bool MenuMode::readHitBoxOffset(Gui3D::PanelElement* e)
{
    if(currentModel)
    {
        for(int i=0; i<3; i++)
        {
            currentModel->hitBoxTranslationOffset.m_floats[i]   = ::atof(hitBoxTranslationZone[i]  ->getValue().c_str());
            currentModel->hitBoxRotationOffset.m_floats[i]      = ::atof(hitBoxRotationZone[i]     ->getValue().c_str());
            currentModel->hitBoxScaleOffset.m_floats[i]         = ::atof(hitBoxScaleZone[i]     ->getValue().c_str());
 
            BtOgre::RigidBodyState* motionState = static_cast< BtOgre::RigidBodyState * >( currentModel->rigidBody->getMotionState() );

            btTransform hitBoxOffset;
            hitBoxOffset.setIdentity();

            hitBoxOffset.setOrigin(currentModel->hitBoxTranslationOffset);

            btQuaternion quatRotation;
            quatRotation.setEuler(  currentModel->hitBoxRotationOffset.getY()/offsetRotPrec,
                                    currentModel->hitBoxRotationOffset.getX()/offsetRotPrec, currentModel->hitBoxRotationOffset.getZ()/offsetRotPrec);
            hitBoxOffset.setRotation(quatRotation);

            btTransform currentTransform;
            motionState->setCenterOfMassOffset(hitBoxOffset);
            motionState->getWorldTransform(currentTransform);
            motionState->setWorldTransform(currentTransform);

            currentModel->rigidBody->getCollisionShape()->setLocalScaling(BtOgre::Convert::toBullet(currentModel->scaleNode->getScale())
                    +currentModel->hitBoxScaleOffset);
        }
    }
    return true;
}
QJSEngine* MenuMode::initScript()
{
    QJSEngine* engine = new QJSEngine();
    Q_INIT_RESOURCE(Scripts);
    QString fileName = ":/testscript.js";
    QFile scriptFile(fileName);
    if (!scriptFile.exists())
        assert(!"JS File not found!!!");
    if (!scriptFile.open(QIODevice::ReadOnly))
        assert(!"JS File not opened!!!");
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();
    engine->evaluate(contents);
    return engine;
}
void MenuMode::initTextColors(QJSEngine* engine)
{
    titleColor = jsToColor( engine->evaluate("TitleColor") );
    textColor  = jsToColor( engine->evaluate("TextColor") );
}
Ogre::ColourValue MenuMode::jsToColor(QJSValue jsArr)
{
    float colors[3];
    for(int i=0; i<3; i++)
    {
        colors[i] = jsArr.property(i).toNumber();
    }
    return Ogre::ColourValue(colors[0], colors[1], colors[2]);
}
