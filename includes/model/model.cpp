#include "model.h"
#include <iostream>
#include <fstream>

bool isBinarySTL(const std::string& STLfileName);
//void readBinarySTL(const std::string& STLfileName);
void readAsciiSTL(const std::string& STLfileName);

model::model() // Could modify to read in filename then determine which initalisation type from there.
{
  // Initalise basic vaeiables:
  numNormals = 0;
  numIndices = 0;
  numMeshNodes = 0;
  numPositions = 0;
  Xmin = 1e+30; Xmax = -1e+30;
  Ymin = 1e+30; Ymax = -1e+30;
  Zmin = 1e+30; Zmax = -1e+30;
}

void model::readSTL(const std::string &STLfileName) // Funstion provides a global means of reading a STL file independent of file type.
{

  if (isBinarySTL(STLfileName))
  {
    readBinarySTL(STLfileName); // Read the binary file type
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
  /*
  free(positions);
  free(vertices);
  free(indices);
  free(normals);
  free(numberOfTriangles);
  free(tempVertex);
  free(tempValueX);
  free(tempValueY);
  free(temp)
  */
}

/////////////////////////////////////////////////////// Local Fucntions:
bool isBinarySTL(const std::string& STLfileName) // Need to find a means of checking file types:
{
  //std::ifstream file;
  //file.open(STLfileName,c_str(), std::ios::binary);
  // Do this later:
  return true;
}

void mesh::readBinarySTL(const std::string& STLfileName) // Read binary file and store in model parameters:
{
  int numberOfTriangles;
  vertex tempVertex;

  float tempValueX, tempValueY, tempValueZ;

  std::ifstream file;
  file.open(STLfileName.c_str(), std::ios::binary | std::ios::in);
  if(file.fail())
  {
    std::cerr << "Could not open binary STL file: " << STLfileName << std::endl;
  }
  else
  {
    file.seekg(80); // Skip the first 80 bytes..
    file.read((char*)&numberOfTriangles, sizeof(int));
    for (unsigned int i = 0; i < numberOfTriangles; i++) // Loop through all facets:
    {

      file.read((char*)&tempValueX, 4); // Store normal component X
      file.read((char*)&tempValueY, 4); // Store normal component Y
      file.read((char*)&tempValueZ, 4); // Store normal component Z

      // Place Normal values into Normal vector:
      tempVertex.normal = glm::vec3((double)tempValueX, (double)tempValueY, (double)tempValueZ); // Will store all the values of the normals, positions and the TexCoords.

      for (unsigned int j = 0; j < 3; j++)
      {
        file.read((char*)&tempValueX, 4); // Store position component X
        file.read((char*)&tempValueY, 4); // Store position component Y
        file.read((char*)&tempValueZ, 4); // Store position component Z

        // Update the verticies value:
        tempVertex.pos = glm::vec3((double)tempValueX, (double)tempValueY, (double)tempValueZ);
        tempVertex.tecCoord = glm::vec2(0,0); // hardcode for now;

        vertices.push_back(tempVertex); numVertices++; // Push back the temp vertex so it contains seperate opties of: normal position and texCoord.

        // Determine view parameters:
        if(tempValueX < Xmin) {Xmin = tempValueX; } // X
        if(temoValueX > Xmax) {Xmax = tempValueX; }
        if(tempValueY < Ymin) {Ymin = tempValueY; } // Y
        if(temoValueY > Ymax) {Ymax = tempValueY; }
        if(tempValueZ < Zmin) {Zmin = tempValueZ; } // Z
        if(temoValueZ > Zmax) {Zmax = tempValueZ; }
      }
    }

    bool match = false;
    indices.push_back(vertices[0]); numIndices++; // Store the first  vertices as an index.
    for (unsigned int i = 0; i < numVertices; i++) // Loop through all vertices and check if it's already located within indicies
    {
         for (unsigned int j = 0; j < numIndices; j++) // Loop through all indices
         {
           if (j ~= i) // skip equal terms
           { // Should probably join these if's....
             if (vertices[i] == indices[j]) // If the values match need to check next i.
             {
               match = true; // set match to true to break out of jth loop.
             }
           }
           if (match) {break;} // break out of jth loop
         }
         // If match stayed false throughout the entire jth loop, values never matched therefore vertex[i] hasn't been accounted for
         // so add it and increment the counter
         if (!match) {indices.push_back(vertices[i]); numIndices++; }
         match = false;
    }

    // Indicies contains all the appropriate information in non repetative format. Loop thourgh and populate sections required for viewing.
    for (unsigned int i = 0; i < numIndices; i++)
    {
      positions.push_back(indices[i].pos); numPositions++;
      normals.push_back(indices[i].normal);
      texCoords.push_pack(indices[i].texCoord);
    }
  } // end of else file opened..
  file.close();
}



void readAsciiSTL(const std::string& STLfileName) // Read ASCII file and store in model parameters:
{
  // Wait until way down the track.....
}
