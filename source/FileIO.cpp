#include "FileIO.h"

void FileIO::writeToFile(std::vector<ModelInfo> modelContainer, const char* filename, const float& offsetRotPrec)
{
    std::ofstream file(filename);
    for(int i=0; i<modelContainer.size(); i++)
    {
        if(modelContainer[i].entity->isVisible())
        {
            Ogre::Vector3 p = modelContainer[i].translationNode->getPosition();
            Ogre::Quaternion r = modelContainer[i].rotationNode->getOrientation();
            Ogre::Vector3 s = modelContainer[i].scaleNode->getScale();
            btQuaternion hbro;
            hbro.setEuler(modelContainer[i].hitBoxRotationOffset.getY()/offsetRotPrec,modelContainer[i].hitBoxRotationOffset.getX()/offsetRotPrec
                        ,modelContainer[i].hitBoxRotationOffset.getZ()/offsetRotPrec);
            file<<"newMesh: "<< modelContainer[i].name<<"\n"
                <<"translation: "   <<"/" <<p.x <<"/" <<p.y <<"/" <<p.z <<"\n"
                <<"rotation: "      <<"/" <<r.w <<"/" <<r.x <<"/" <<r.y <<"/" <<r.z <<"\n"
                <<"scale: "         <<"/" <<s.x <<"/" <<s.y <<"/" <<s.z <<"\n"
                <<"shapeType: "     <<modelContainer[i].hitboxShapeType <<"\n"
                <<"hitBoxOffsetTranslation: "
                <<"/" <<modelContainer[i].hitBoxTranslationOffset.getX()
                <<"/" <<modelContainer[i].hitBoxTranslationOffset.getY()
                <<"/" <<modelContainer[i].hitBoxTranslationOffset.getZ()<<"\n"
                <<"hitBoxOffsetRotation: "
                <<"/" <<hbro.getX()
                <<"/" <<hbro.getY()
                <<"/" <<hbro.getZ()
                <<"/" <<hbro.getW()<<"\n"
                <<"hitBoxOffsetScale: "
                <<"/" <<modelContainer[i].hitBoxScaleOffset.getX()
                <<"/" <<modelContainer[i].hitBoxScaleOffset.getY()
                <<"/" <<modelContainer[i].hitBoxScaleOffset.getZ()<<"\n";
        }
    }
    file.close();
}
std::vector<ModelGenes> FileIO::readFile(const char* filename)
{

    std::ifstream file(filename);
    std::string line;
    std::vector<ModelGenes> mInfo;
    int index=-1;
    while(file.good())
    {
        std::getline(file,line);
        if(beginsWith(line,"newMesh"))
        {
            mInfo.push_back(ModelGenes());
            index = mInfo.size()-1;
            mInfo[index].name = line.substr(8);
            mInfo[index].filename = line.substr(11);
        }
        else if(beginsWith(line,"translation"))
        {
            std::istringstream sValues(line.substr(14));
            std::string valueStr;
            float values[3];
            int i=0;
            while(std::getline(sValues,valueStr,'/'))
            {
                 values[i] = stringToFloat(valueStr);
                 i++;
            }
            mInfo[index].translation.x = values[0];
            mInfo[index].translation.y = values[1];
            mInfo[index].translation.z = values[2];
        }
        else if(beginsWith(line,"rotation"))
        {
            std::istringstream sValues(line.substr(11));
            std::string value;
            float values[4];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].rotation.w = values[0];
            mInfo[index].rotation.x = values[1];
            mInfo[index].rotation.y = values[2];
            mInfo[index].rotation.z = values[3];
        }
        else if(beginsWith(line,"scale"))
        {
            std::istringstream sValues(line.substr(8));
            std::string value;
            float values[3];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].scale.x = values[0];
            mInfo[index].scale.y = values[1];
            mInfo[index].scale.z = values[2];
        }
        else if(beginsWith(line,"shapeType"))
        {
            mInfo[index].hitboxShapeType = line.substr(11);
        }
        else if(beginsWith(line,"hitBoxOffsetTranslation"))
        {
            std::istringstream sValues(line.substr(26));
            std::string value;
            float values[3];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].hitBoxTranslationOffset.setX(values[0]);
            mInfo[index].hitBoxTranslationOffset.setY(values[0]);
            mInfo[index].hitBoxTranslationOffset.setZ(values[0]);
        }
        else if(beginsWith(line,"hitBoxOffsetRotation"))
        {
            std::istringstream sValues(line.substr(23));
            std::string value;
            float values[4];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].hitBoxRotationOffset.setX(values[0]);
            mInfo[index].hitBoxRotationOffset.setY(values[1]);
            mInfo[index].hitBoxRotationOffset.setZ(values[2]);
            mInfo[index].hitBoxRotationOffset.setW(values[3]);
        }
        else if(beginsWith(line,"hitBoxOffsetScale"))
        {
            std::istringstream sValues(line.substr(20));
            std::string value;
            float values[3];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].hitBoxScaleOffset.setX(values[0]);
            mInfo[index].hitBoxScaleOffset.setY(values[0]);
            mInfo[index].hitBoxScaleOffset.setZ(values[0]);
        }

    }
    return mInfo;
}
float FileIO::stringToFloat(std::string str)
{
    float f;
    std::istringstream ss(str);
    ss>>f;
    return f; 
}
bool FileIO::beginsWith(std::string value, std::string bValue)
{
    for(int i=0; i<bValue.length(); i++)
    {
        if(value[i] != bValue[i])
        {
            return false;
        }
    }
    return true;
}





//out of order
//until further notice
//
/*
std::vector<ModelInfo> FileIO::readFile(const char* filename, Ogre::SceneManager * scMgr)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<ModelInfo> mInfo;
    int index=-1;
    while(file.good())
    {
        std::getline(file,line);
        if(beginsWith(line,"newMesh"))
        {
            mInfo.push_back(ModelInfo());
            index = mInfo.size()-1;
            mInfo[index].name = line.substr(8);
        }
        else if(beginsWith(line,"translation"))
        {
            std::istringstream sValues(line.substr(14));
            std::string value;
            float values[3];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].translationNode = scMgr->getRootSceneNode()->createChildSceneNode("Read/"+mInfo[index].name+"/translation");
            mInfo[index].translationNode->setPosition(values[0],values[1],values[2]);
        }
        else if(beginsWith(line,"rotation"))
        {
            std::istringstream sValues(line.substr(11));
            std::string value;
            float values[4];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].rotationNode = mInfo[index].translationNode->createChildSceneNode("Read/"+mInfo[index].name+"/rotation");
            mInfo[index].rotationNode->setOrientation(values[0],values[1],values[2],values[3]);
        }
        else if(beginsWith(line,"scale"))
        {
            std::istringstream sValues(line.substr(8));
            std::string value;
            float values[3];
            int i=0;
            while(std::getline(sValues,value,'/'))
            {
                 values[i] = stringToFloat(value);
                 i++;
            }
            mInfo[index].scaleNode = mInfo[index].rotationNode->createChildSceneNode("Read/"+mInfo[index].name+"/translation/Read");
            mInfo[index].scaleNode->setScale(values[0],values[1],values[2]);
            std::istringstream meshURLStream(mInfo[index].name);
            std::string meshURL[3];
            i=0;
            while(std::getline(meshURLStream,meshURL[i],'/')){
                    i++;
            }
            mInfo[index].entity = scMgr->createEntity(meshURL[1]);
            mInfo[index].scaleNode->attachObject(mInfo[index].entity);
        }
    }
    file.close();
    return mInfo;
}
*/
