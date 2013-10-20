#include "Mode.h"

OgreFramework*              Mode::rEngine=NULL;
unsigned int                Mode::modelsPlaced=0;
Ogre::SceneNode *           Mode::currentNode=NULL;
Gui3D::Caption*             Mode::captionCombobox=NULL;
std::vector<Ogre::String>   Mode::totalModels;
std::vector<Ogre::String>   Mode::addedModels;
std::vector<Ogre::Entity*>  Mode::entitys;
std::vector<Mode::modelInfo>Mode::models;

Gui3D::Combobox*            Mode::addedCombobox=NULL;
Gui3D::Panel*               Mode::panel=NULL;

int                         Mode::_widthPadding = 20;
int                         Mode::_width        = 400;
int                         Mode::_height       = 400;
int                         Mode::_distance     = 100;
int                         Mode::_wP           = Mode::_width-Mode::_widthPadding;
int                         Mode::_boxHeight    = Mode::_width/2;

Mode::Mode()
{
    rEngine = OgreFramework::getSingletonPtr();
}

bool Mode::selectModel(Gui3D::Combobox* e)
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
bool Mode::addModel(Gui3D::Combobox* e)
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
bool Mode::hasEnding(std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
