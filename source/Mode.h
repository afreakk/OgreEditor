
#ifndef MODE_H
#define MODE_H
#include "OgreFramework.h"
#include "FileIO.h"
#include "Gui3D.h"
#include "Gui3DPanel.h"
class Mode
{
    public:
        Mode();
        ~Mode();
        virtual void update(double)=0;
        virtual void init()=0;
        virtual bool keyPressed(const OIS::KeyEvent &keyEventRef)=0;
        virtual bool keyReleased(const OIS::KeyEvent &keyEventRef)=0;
        virtual bool mouseMoved(const OIS::MouseEvent &evt)=0;
        virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)=0;
        virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)=0;
    protected:
        std::string createModelFileIndex(Ogre::String modelName);
        void makeCombobox(std::string& totalName);
        void destroyCombobox();
        void setCaptionText(std::string modelName);
        void moveModel();
        bool selectModel(Gui3D::Combobox* e);
        bool addModel(Gui3D::Combobox* e); 
        bool hasEnding(std::string const &fullString, std::string const &ending); 
        void addToComboBox(std::string modelName);
        static OgreFramework* rEngine;
        static unsigned int modelsPlaced;
        static ModelInfo * currentModel;
        static std::vector<Ogre::String> totalModels;
        static std::vector<Ogre::String> addedModels;
        static Gui3D::Caption* captionCombobox;
        static std::vector<ModelInfo> modelContainer;
        static Gui3D::Combobox* addedCombobox;
        static Gui3D::Panel* panel;
        static int _widthPadding;
        static int _width;
        static int _height;
        static int _distance;
        static int _wP;
        static int _boxHeight;
        static float modelDistance;
        static float zDistance;

};
#endif /*MODE_H*/
