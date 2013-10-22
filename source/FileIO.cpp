#include "FileIO.h"

void FileIO::writeToFile(std::vector<ModelInfo> modelContainer, const char* filename)
{
    std::ofstream file;
    file.open(filename);
    for(int i=0; i<modelContainer.size(); i++)
    {
        file <<"newMesh: "<< modelContainer[i].name<<"\n";
        file <<"scale: "<< modelContainer[i].scaleNode->getScale()<<"\n";
        file <<"rotation: "<< modelContainer[i].rotationNode->getOrientation()<<"\n";
        file <<"translation: "<<modelContainer[i].rotationNode->getPosition()<<"\n";
    }

}
