#include "model.h"

#include <iostream>
#include <fstream>

bool isBinarySTL(const std::string& STLfileName);
void readBinarySTL(const std::string& STLfileName);
void readAsciiSTL(const std::string& STLfileName);

model::model()
{
  // constructure: (set values for a black cube)
}

void model::readSTL(const std::string &STLfileName) // Funstion provides a global means of reading a STL file independent of file type.
{

  if (isBinarySTL(STLfileName))
  {
    readBinarySTL(STLfileName);
  }
  else
  {
    readAsciiSTL(STLfileName); // Probably wont worry about this at all.
  }

}

void model::readModel(const std::string &modelFileName) // will read purely binary file types (model output from computer vision algorithm)
{
  // will have to set up structure definitions for this...
}

void readPointCloud(const std::string &pointCloudFileNAme)
{
  // Will be important for the model to loop at the keypoint mappings
}

model::~model()
{

}

/////////////////////////////////////////////////////// Local Fucntions:
bool isBinarySTL(const std::string& STLfileName)
{
  //std::ifstream file;
  //file.open(STLfileName,c_str(), std::ios::binary);
  // Do this later:
  return true;
}

void readBinarySTL(const std::string& STLfileName) // Read binary file and store in model parameters:
{

}

void readAsciiSTL(const std::string& STLfileName) // Read ASCII file and store in model parameters:
{
  // Wait until way down the track.....
}
