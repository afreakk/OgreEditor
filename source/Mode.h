#ifndef MODE_H
#define MODE_H
#include "OgreFramework.h"
#include "FileIO.h"
#include "Gui3D.h"
#include "Gui3DPanel.h"
#include "world.h"
#include "InputHandling.h"

class Mode
{
    public:
        Mode();
        ~Mode();
        virtual void update(const Ogre::FrameEvent&)=0;
        virtual void init()=0;
        virtual bool keyPressed(const OIS::KeyEvent &keyEventRef)=0;
        virtual bool keyReleased(const OIS::KeyEvent &keyEventRef)=0;
        virtual bool mouseMoved(const OIS::MouseEvent &evt)=0;
        virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)=0;
        virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)=0;
        void setWorld(World* _world);
        void setInput(InputHandling* _input);
    protected:
        std::string createModelFileIndex(Ogre::String modelName);
        void makeCombobox(std::string& totalName);
        void destroyCombobox();
        void setCaptionText(std::string modelName);
        void moveModel();
        void addToComboBox(std::string modelName);
        void getNewTextZoneValues(ModelInfo*);
        bool selectModel(Gui3D::Combobox* e);
        bool addModel(Ogre::String name); 
        bool hasEnding(std::string const &fullString, std::string const &ending); 
        int hitboxSelection(Ogre::String shapeName);
        std::string stringToFloat(float number);

        static World* world;
        static OgreFramework* rEngine;
        static InputHandling* input;
        static unsigned int modelsPlaced;
        static ModelInfo * currentModel;
        static std::vector<Ogre::String> totalModels;
        static std::vector<Ogre::String> addedModels;
        static Gui3D::Caption* captionCombobox;
        static std::vector<ModelInfo> modelContainer;
        static Gui3D::Combobox* addedCombobox;
        static Gui3D::Panel* panel;
        static Gui3D::InlineSelector* shapeTypeSelector;
        static Gui3D::TextZone* hitBoxTranslationZone[3];
        static Gui3D::TextZone* hitBoxRotationZone[3];
        static Gui3D::TextZone* hitBoxScaleZone[3];
        static const float offsetRotPrec;
        static const int _widthPadding;
        static const int _width;
        static const int _height;
        static const int _distance;
        static const int _wP;
        static const int _boxHeight;
        static const float modelDistance;
        static float zDistance;
        const static std::string noneSelected; 

};
#endif /*MODE_H*/
