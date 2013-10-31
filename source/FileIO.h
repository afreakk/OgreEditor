#ifndef FILEIO_H
#define FILEIO_H

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "rigidbody.h"
struct ModelInfo
{
    Ogre::String name;
    Ogre::SceneNode* translationNode;
    Ogre::SceneNode* rotationNode;
    Ogre::SceneNode* scaleNode;
    Ogre::Entity* entity;
    RigidBody* rigidBody;
};

class FileIO
{
    public:
        static void writeToFile(std::vector<ModelInfo> modelContainer, const char* filename);
        static std::vector<ModelInfo> readFile(const char* filename, Ogre::SceneManager * scMgr);
        static bool beginsWith(std::string value, std::string bValue);
        static float stringToFloat(std::string str);
};

#endif /*FILEIO_H*/
