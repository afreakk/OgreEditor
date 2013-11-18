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
    Ogre::String hitboxShapeType;
    btVector3 hitBoxTranslationOffset;
    btVector3 hitBoxRotationOffset;
    btVector3 hitBoxScaleOffset;
    ModelInfo():
        hitBoxTranslationOffset(    btVector3(0.0, 0.0, 0.0)    ) ,
        hitBoxRotationOffset(    btVector3(0.0, 0.0, 0.0)    ) ,
        hitBoxScaleOffset(    btVector3(0.0, 0.0, 0.0)    ) 
    {}
};
struct ModelGenes
{
    Ogre::String name;
    Ogre::String filename;
    Ogre::Vector3 translation;
    Ogre::Quaternion rotation;
    Ogre::Vector3 scale;
    Ogre::String hitboxShapeType;
    btVector3 hitBoxTranslationOffset;
    btQuaternion hitBoxRotationOffset;
    btVector3 hitBoxScaleOffset;
};

class FileIO
{
    public:
        static void writeToFile(std::vector<ModelInfo> modelContainer, const char* filename, const float& offsetRotPrec);
        static std::vector<ModelGenes> readFile(const char* filename);
        //static std::vector<ModelInfo> readFile(const char* filename, Ogre::SceneManager * scMgr);
        static bool beginsWith(std::string value, std::string bValue);
        static float stringToFloat(std::string str);
};

#endif /*FILEIO_H*/
