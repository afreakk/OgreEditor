#include "Mode.h"

World*                      Mode::world         =NULL;

OgreFramework*              Mode::rEngine       =NULL;
InputHandling*              Mode::input         =NULL;
unsigned int                Mode::modelsPlaced  =0;
ModelInfo*                  Mode::currentModel  =NULL;
Gui3D::Caption*             Mode::captionCombobox=NULL;
Gui3D::TextZone*            Mode::hitBoxTranslationZone[3];
Gui3D::TextZone*            Mode::hitBoxRotationZone[3];
Gui3D::TextZone*            Mode::hitBoxScaleZone[3];

std::vector<Ogre::String>   Mode::totalModels;
std::vector<Ogre::String>   Mode::addedModels;
std::vector<ModelInfo>      Mode::modelContainer;

Gui3D::Combobox*            Mode::addedCombobox =NULL;
Gui3D::Panel*               Mode::panel         =NULL;
Gui3D::InlineSelector*      Mode::shapeTypeSelector= NULL;

const int                   Mode::_widthPadding = 20;
const int                   Mode::_width        = 400;
const int                   Mode::_height       = 640;
const int                   Mode::_distance     = 100;
const int                   Mode::_wP           = Mode::_width-Mode::_widthPadding;
const int                   Mode::_boxHeight    = Mode::_width/2;

const float                 Mode::offsetRotPrec=100.0;

const float                 Mode::modelDistance =4.0f;
float                       Mode::zDistance     =0.0f;

const std::string           Mode::noneSelected = "None";

Mode::Mode()
{
    rEngine = OgreFramework::getSingletonPtr();
}

Mode::~Mode()
{

}

void Mode::getNewTextZoneValues(ModelInfo * what)
{
    if(what)
    {
        for(int i=0; i<3; i++)
        {
            hitBoxRotationZone[i]->setValue(    stringToFloat( what->hitBoxRotationOffset.m_floats[i]    ) );
            hitBoxTranslationZone[i]->setValue( stringToFloat( what->hitBoxTranslationOffset.m_floats[i] ) ); 
            hitBoxScaleZone[i]->setValue( stringToFloat( what->hitBoxScaleOffset.m_floats[i] ) ); 
        }
    }
    else
    {
        for(int i=0; i<3; i++)
        {
            hitBoxRotationZone[i]->setValue(    "0" );
            hitBoxTranslationZone[i]->setValue( "0" );
            hitBoxScaleZone[i]->setValue( "0" );
        }
    }
}

void Mode::setInput(InputHandling* _input)
{
    input = _input;
}

std::string Mode::stringToFloat(float number)
{
      std::ostringstream buff;
      buff  <<  number;
      return buff.str();
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
                shapeTypeSelector->setCurrentValue(currentModel->hitboxShapeType);
                int shapeType = hitboxSelection(currentModel->hitboxShapeType);
                currentModel->rigidBody = world->addRigidBody(0,currentModel->entity,shapeType);
                currentModel->entity->setVisible(true);
                getNewTextZoneValues(NULL);
            }
            else
            {
                shapeTypeSelector->setCurrentValue(currentModel->hitboxShapeType);
                getNewTextZoneValues(currentModel);
            }
        }
    }
    zDistance=0.0f;
    moveModel();
}

int Mode::hitboxSelection(Ogre::String shapeName)
{
    if(shapeName == "Sphere") return Shapez::sphere;
    if(shapeName ==  "Box") return Shapez::box;
    if(shapeName ==  "Trimesh") return Shapez::trimesh;
    if(shapeName ==  "Cylinder") return Shapez::cylinder;
    if(shapeName ==  "Convex") return Shapez::convex;
    if(shapeName ==  "Capsule") return Shapez::capsule;
    assert(!"failure in Mode::hitboxSelection");
}

std::string Mode::createModelFileIndex(Ogre::String modelName)
{
    std::ostringstream x;
    x << modelsPlaced <<"/"<<modelName;
    return x.str();
}

bool Mode::addModel(Ogre::String name)
{
    modelsPlaced++;
    ModelInfo temp;
    temp.name = createModelFileIndex(name);
    temp.translationNode = rEngine->m_pSceneMgr->getRootSceneNode()->createChildSceneNode(temp.name+"/position");
    temp.rotationNode = temp.translationNode->createChildSceneNode(temp.name+"/orientation");
    temp.scaleNode = temp.rotationNode->createChildSceneNode(temp.name+"/scale");
    temp.entity = rEngine->m_pSceneMgr->createEntity(temp.name,name);
    temp.entity->setVisible(false);
    temp.hitboxShapeType = "Trimesh";
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
    if (fullString.length() >= ending.length()) 
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    else
        return false;
}

void Mode::moveModel()
{
    if(currentModel)
    {
        currentModel->translationNode->setPosition(rEngine->mFPC->getPosition());

        Ogre::Quaternion cameraRotation(rEngine->mFPC->getOrientation());
        Ogre::Vector3 transVector(0.0f,0.0f,-(zDistance+modelDistance*currentModel->entity->getBoundingBox().getMaximum().z));

        transVector = cameraRotation*transVector;
        currentModel->translationNode->translate(transVector,Ogre::Node::TS_WORLD);

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

