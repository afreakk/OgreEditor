#ifndef FILEIO_H
#define FILEIO_H

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <vector>
#include <fstream>
struct ModelInfo
{
    Ogre::String name;
    Ogre::SceneNode* translationNode;
    Ogre::SceneNode* rotationNode;
    Ogre::SceneNode* scaleNode;
    Ogre::Entity* entity;
};

class FileIO
{
    public:
        static void writeToFile(std::vector<ModelInfo> modelContainer, const char* filename);
};

#endif /*FILEIO_H*/
