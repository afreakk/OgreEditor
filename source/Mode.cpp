#include "Mode.h"

OgreFramework*              Mode::rEngine       =NULL;
unsigned int                Mode::modelsPlaced  =0;
ModelInfo*            Mode::currentModel  =NULL;
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
Mode::Mode()
{
    rEngine = OgreFramework::getSingletonPtr();
}

Mode::~Mode()
{
}
bool Mode::selectModel(Gui3D::Combobox* e)
{
    Ogre::String _name = e->getValue();
    for(int i=0; i<modelContainer.size(); i++)
    {
        if(_name == modelContainer[i].name)
        {
            currentModel = &modelContainer[i];
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
    temp.scaleNode->attachObject(temp.entity);
    modelContainer.push_back(temp);

    addedModels.push_back(temp.name);
    addToComboBox(temp.name);
	return true;
}
void Mode::addToComboBox(std::string modelName)
{
    setCaptionText(modelName);
    destroyCombobox();
    makeCombobox(modelName);
    selectModel(addedCombobox);
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
    addedCombobox->highlight();
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
        currentModel->translationNode->translate(0.0f,0.0f,-(zDistance+modelDistance*currentModel->entity->getBoundingBox().getMaximum().z)
                ,Ogre::Node::TS_LOCAL);
    }
}
