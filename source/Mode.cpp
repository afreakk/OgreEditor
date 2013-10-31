#include "Mode.h"

World*                      Mode::world         =NULL;

OgreFramework*              Mode::rEngine       =NULL;
InputHandling*              Mode::input         =NULL;
unsigned int                Mode::modelsPlaced  =0;
ModelInfo*                  Mode::currentModel  =NULL;
Gui3D::Caption*             Mode::captionCombobox=NULL;

std::vector<Ogre::String>   Mode::totalModels;
std::vector<Ogre::String>   Mode::addedModels;
std::vector<ModelInfo>Mode::modelContainer;

Gui3D::Combobox*            Mode::addedCombobox =NULL;
Gui3D::Panel*               Mode::panel         =NULL;

int                         Mode::_widthPadding = 20;
int                         Mode::_width        = 400;
int                         Mode::_height       = 400;
int                         Mode::_distance     = 100;
int                         Mode::_wP           = Mode::_width-Mode::_widthPadding;
int                         Mode::_boxHeight    = Mode::_width/2;

float                       Mode::modelDistance =4.0f;
float                       Mode::zDistance     =0.0f;

std::string                 Mode::noneSelected = "Select Model for placing";

Mode::Mode()
{
    rEngine = OgreFramework::getSingletonPtr();
}

Mode::~Mode()
{
}
void Mode::setInput(InputHandling* _input)
{
    input = _input;
}
bool Mode::selectModel(Gui3D::Combobox* e)
{
    Ogre::String _name = e->getValue();
    for(int i=0; i<modelContainer.size(); i++)
    {
        if(_name == modelContainer[i].name)
        {
            currentModel = &modelContainer[i];
            setCaptionText(currentModel->name);
            if(!currentModel->entity->getVisible())
            {
                currentModel->rigidBody = world->addRigidBody(0,currentModel->entity,Shapez::convex);
                currentModel->entity->setVisible(true);
            }
        }
    }
    zDistance=0.0f;
    moveModel();
}
std::string Mode::createModelFileIndex(Ogre::String modelName)
{
    std::ostringstream x;
    x << modelsPlaced <<"/"<<modelName;
    return x.str();
}
bool Mode::addModel(Gui3D::Combobox* e)
{
    modelsPlaced++;
    ModelInfo temp;
    temp.name = createModelFileIndex(e->getValue());
    temp.translationNode = rEngine->m_pSceneMgr->getRootSceneNode()->createChildSceneNode(temp.name+"/position");
    temp.rotationNode = temp.translationNode->createChildSceneNode(temp.name+"/orientation");
    temp.scaleNode = temp.rotationNode->createChildSceneNode(temp.name+"/scale");
    temp.entity = rEngine->m_pSceneMgr->createEntity(temp.name,e->getValue());
    temp.entity->setVisible(false);
    temp.scaleNode->attachObject(temp.entity);
    modelContainer.push_back(temp);
    addedModels.push_back(temp.name);
    addToComboBox(temp.name);
	return true;
}
void Mode::addToComboBox(std::string modelName)
{
    destroyCombobox();
    makeCombobox(modelName);
}
void Mode::setCaptionText(std::string modelName)
{
    std::ostringstream s;
    s << "Selected: " << modelName;
    captionCombobox->text(s.str());
}
void Mode::destroyCombobox()
{
    if(addedCombobox)
        panel->destroyCombobox(addedCombobox);
    delete addedCombobox;
}
void Mode::makeCombobox(std::string& totalName)
{
    addedCombobox = panel->makeCombobox(_widthPadding/2,_boxHeight*1.2,_wP,_boxHeight*0.8,addedModels,5);
    addedCombobox->setCurrentValue(totalName);
}
bool Mode::hasEnding(std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
void Mode::moveModel()
{
    if(currentModel)
    {
        currentModel->translationNode->setPosition(rEngine->mFPC->getPosition());
        currentModel->translationNode->setOrientation(rEngine->mFPC->getOrientation());
        currentModel->translationNode->translate(0.0f,0.0f,-(zDistance+modelDistance*currentModel->entity->getBoundingBox()
                    .getMaximum().z),Ogre::Node::TS_LOCAL);
        btTransform bTrans;
        Ogre::Vector3 ogreV = currentModel->translationNode->getPosition();
        Ogre::Quaternion ogreQr = currentModel->translationNode->getOrientation();
        Ogre::Quaternion ogreQt = currentModel->rotationNode->getOrientation();
        ogreQr = ogreQr * ogreQt;
        Ogre::Vector3 ogreS = currentModel->scaleNode->getScale();
        btQuaternion rotation = btQuaternion(ogreQr.x,ogreQr.y,ogreQr.z,ogreQr.w);
        btVector3 origin = btVector3(ogreV.x,ogreV.y,ogreV.z);
        bTrans.setRotation(rotation);
        bTrans.setOrigin(origin);
        currentModel->rigidBody->setCenterOfMassTransform(bTrans);
    }
}
void Mode::setWorld(World* _world)
{
    world = _world;
}
