#include "model.h"
#include <iostream>
#include <fstream>
#include <math.h>


bool isBinarySTL(const std::string& STLfileName);
void readBinarySTL(const std::string& STLfileName, model& myModel);
void readAsciiSTL(const std::string& STLfileName, model& myModel);

void readSTL(const std::string& STLfileName, model& myModel);                // will read either binary or Ascii file types.
      // Will also initalise the model type relating to STL files thus locking curtin variable access
void readModel(const std::string& STLfileName, model& myModel);            // will read purely binary file types (model output from computer vision algorithm)
      // Will also initalise the model type relating to model files thus locking curtin variable access
void readPointCloud(const std::string& STLfileName, model& myModel);  // will allow to read in point clouds
      // Will also initalise the model type relating to Point Clouds files thus locking curtin variable access


model::model(const std::string& fileName) // Could modify to read in filename then determine which initalisation type from there.
{
  // Determine the file extension:
  std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
  if (extension.size()  < 1 )
  {
    std::cerr << "Error: could not determine file extension." << std::endl;
  }
  else
  {
    if (extension == "STL" || extension == "stl")
    {
      readSTL(fileName, *this);
    }
    else if (extension == "PCD" || extension == "pcd")
    {
      // Run point cloud code
    }
    else
    {
      std::cerr << "Incompatable file extension...." << std::endl;
    }
  }
}

model::~model() // Destructor:
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

void readSTL(const std::string& STLfileName, model& myModel) // Funstion provides a global means of reading a STL file independent of file type.
{

  if (isBinarySTL(STLfileName))
  {
    readBinarySTL(STLfileName, myModel); // Read the binary file type
    /*
    myModel.positions.push_back(glm::vec3(-1, -1, -1));
    myModel.texCoords.push_back(glm::vec2(1, 0));
    myModel.normals.push_back(glm::vec3(0, 0, -1));
    myModel.positions.push_back(glm::vec3(-1, 1,-1));
    myModel.texCoords.push_back(glm::vec2(0, 0));
    myModel.normals.push_back(glm::vec3(0, 0, -1));
		myModel.positions.push_back(glm::vec3(1, 1, -1));
    myModel.texCoords.push_back(glm::vec2(0, 1));
    myModel.normals.push_back(glm::vec3(0, 0, -1));
		myModel.positions.push_back(glm::vec3(1, -1, -1));
    myModel.texCoords.push_back(glm::vec2(1, 1));
    myModel.normals.push_back(glm::vec3(0, 0, -1));

		myModel.positions.push_back(glm::vec3(-1, -1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 0));
    myModel.normals.push_back(glm::vec3(0, 0, 1));
		myModel.positions.push_back(glm::vec3(-1, 1, 1));
    myModel.texCoords.push_back(glm::vec2(0, 0));
    myModel.normals.push_back(glm::vec3(0, 0, 1));
		myModel.positions.push_back(glm::vec3(1, 1, 1));
    myModel.texCoords.push_back(glm::vec2(0, 1));
    myModel.normals.push_back(glm::vec3(0, 0, 1));
		myModel.positions.push_back(glm::vec3(1, -1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 1));
    myModel.normals.push_back(glm::vec3(0, 0, 1));

		myModel.positions.push_back(glm::vec3(-1, -1, -1));
    myModel.texCoords.push_back(glm::vec2(0, 1));
    myModel.normals.push_back(glm::vec3(0, -1, 0));
		myModel.positions.push_back(glm::vec3(-1, -1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 1));
    myModel.normals.push_back(glm::vec3(0, -1, 0));
		myModel.positions.push_back(glm::vec3(1, -1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 0));
    myModel.normals.push_back(glm::vec3(0, -1, 0));
		myModel.positions.push_back(glm::vec3(1, -1, -1));
    myModel.texCoords.push_back(glm::vec2(0, 0));
    myModel.normals.push_back(glm::vec3(0, -1, 0));

		myModel.positions.push_back(glm::vec3(-1, 1, -1));
    myModel.texCoords.push_back(glm::vec2(0, 1));
    myModel.normals.push_back(glm::vec3(0, 1, 0));
		myModel.positions.push_back(glm::vec3(-1, 1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 1));
    myModel.normals.push_back(glm::vec3(0, 1, 0));
		myModel.positions.push_back(glm::vec3(1, 1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 0));
    myModel.normals.push_back(glm::vec3(0, 1, 0));
		myModel.positions.push_back(glm::vec3(1, 1, -1));
    myModel.texCoords.push_back(glm::vec2(0, 0));
    myModel.normals.push_back(glm::vec3(0, 1, 0));

		myModel.positions.push_back(glm::vec3(-1, -1, -1));
    myModel.texCoords.push_back(glm::vec2(1, 1));
    myModel.normals.push_back(glm::vec3(-1, 0, 0));
		myModel.positions.push_back(glm::vec3(-1, -1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 0));
    myModel.normals.push_back(glm::vec3(-1, 0, 0));
		myModel.positions.push_back(glm::vec3(-1, 1, 1));
    myModel.texCoords.push_back(glm::vec2(0, 0));
    myModel.normals.push_back(glm::vec3(-1, 0, 0));
		myModel.positions.push_back(glm::vec3(-1, 1, -1));
    myModel.texCoords.push_back(glm::vec2(0, 1));
    myModel.normals.push_back(glm::vec3(-1, 0, 0));

		myModel.positions.push_back(glm::vec3(1, -1, -1));
    myModel.texCoords.push_back(glm::vec2(1, 1));
    myModel.normals.push_back(glm::vec3(1, 0, 0));
		myModel.positions.push_back(glm::vec3(1, -1, 1));
    myModel.texCoords.push_back(glm::vec2(1, 0));
    myModel.normals.push_back(glm::vec3(1, 0, 0));
		myModel.positions.push_back(glm::vec3(1, 1, 1));
    myModel.texCoords.push_back(glm::vec2(0, 0));
    myModel.normals.push_back(glm::vec3(1, 0, 0));
		myModel.positions.push_back(glm::vec3(1, 1, -1));
    myModel.texCoords.push_back(glm::vec2(0, 1));
    myModel.normals.push_back(glm::vec3(1, 0, 0));

                  myModel.indices.push_back(0);
                  myModel.indices.push_back(1);
                  myModel.indices.push_back(2);
                  myModel.indices.push_back(0);
                  myModel.indices.push_back(2);
                  myModel.indices.push_back(3 );
                  myModel.indices.push_back(6 );
                  myModel.indices.push_back(5 );
                  myModel.indices.push_back(4 );meshLINES
                  myModel.indices.push_back(8 );
                  myModel.indices.push_back(11);
                  myModel.indices.push_back(10);
                  myModel.indices.push_back(8 );
                  myModel.indices.push_back(12);
                  myModel.indices.push_back(13);
                  myModel.indices.push_back(14);
                  myModel.indices.push_back(12);
                  myModel.indices.push_back(14);
                  myModel.indices.push_back(15);
                  myModel.indices.push_back(16);
                  myModel.indices.push_back(17);
                  myModel.indices.push_back(18);
                  myModel.indices.push_back(16);
                  myModel.indices.push_back(18);
                  myModel.indices.push_back(19);
                  myModel.indices.push_back(22);
                  myModel.indices.push_back(21);
                  myModel.indices.push_back(20);
                  myModel.indices.push_back(23 );
                  myModel.indices.push_back(22 );
                  myModel.indices.push_back(20);
                  */
  }
  else
  {
    readAsciiSTL(STLfileName, myModel); // Probably wont worry about this at all.
  }

}

void readModel(const std::string &modelFileName) // will read purely binary file types (model output from computer vision algorithm)
{
  // will have to set up structure definitions for this...
}

void readPointCloud(const std::string &pointCloudFileNAme)
{
  // Will be important for the model to loop at the keypoint mappings
}


/////////////////////////////////////////////////////// Local Fucntions:
bool isBinarySTL(const std::string& STLfileName) // Need to find a means of checking file types:
{
  //std::ifstream file;
  //file.open(STLfileName,c_str(), std::ios::binary);
  // Do this later:
  return true;
}

void readBinarySTL(const std::string& STLfileName, model& myModel) // Read binary file and store in model parameters:
{
  int numberOfTriangles; // This will be red in otder to determine the number of Facets to be read.
  float tempValueX, tempValueY, tempValueZ, tempNormX, tempNormY, tempNormZ;

  std::ifstream file;
  file.open(STLfileName.c_str(), std::ios::binary|std::ios::in);
  if(file.fail())
  {
    std::cerr << "Could not open binary STL file: " << STLfileName << std::endl;
  }
  else
  {
    file.seekg(80); // Skip the first 80 bytes..
    file.read((char*)&numberOfTriangles, sizeof(int));
    char unusedBytes[2];
    unsigned int counter = 0;
    std::cout << "Number of Facets: " << numberOfTriangles << std::endl;
    for (unsigned int i = 0; i < numberOfTriangles; i++) // Loop through all facets:
    {
      file.read((char*)&tempNormX, 4); // Store normal component X
      file.read((char*)&tempNormY, 4); // Store normal component Y
      file.read((char*)&tempNormZ, 4); // Store normal component Z

      // Will store all the values of the normals, positions and the TexCoords.

      for (unsigned int j = 0; j < 3; j++)
      {
        file.read((char*)&tempValueX, 4); // Store position component X
        file.read((char*)&tempValueY, 4); // Store position component Y
        file.read((char*)&tempValueZ, 4); // Store position component Z

        // Update the verticies value: (Will store all information from STL file)
      //  std::cout << "Normal: " << tempValueX << "\t" << "Absolue: " << fabs(tempValueX) << std::endl;
        if (fabs(tempValueX) < 0.000000001) {tempValueX = 0;}
        if (fabs(tempValueY) < 0.000000001) {tempValueY = 0;}
        if (fabs(tempValueZ) < 0.000000001) {tempValueZ = 0;}

        myModel.positions.push_back(glm::vec3((double)tempValueX, (double)tempValueY, (double)tempValueZ));
        myModel.texCoords.push_back(glm::vec2(0,0)); // hardcode for now
        myModel.normals.push_back(glm::vec3((double)tempValueX, (double)tempValueY, (double)tempValueZ)); // Push back the temp vertex so it contains seperate opties of: normal position and texCoord.
        myModel.numPositions++;
        myModel.indices.push_back(counter); counter++;

        // Determine view parameters:
        if(tempValueX < myModel.Xmin) {myModel.Xmin = tempValueX; } // X
        if(tempValueX > myModel.Xmax) {myModel.Xmax = tempValueX; }
        if(tempValueY < myModel.Ymin) {myModel.Ymin = tempValueY; } // Y
        if(tempValueY > myModel.Ymax) {myModel.Ymax = tempValueY; }
        if(tempValueZ < myModel.Zmin) {myModel.Zmin = tempValueZ; } // Z
        if(tempValueZ > myModel.Zmax) {myModel.Zmax = tempValueZ; }
      }
      file.read(unusedBytes,2);
    }
      // Sorting Algorthim:
      /*
      std::vector< std::vector<unsigned int> >  HashTable(myModel.numPositions, std::vector<unsigned int> (myModel.numPositions)); // Square matrix numPositions * numPositions;
      bool skipVal = false;
      unsigned int count = 1;

      for (unsigned int i = 0; i < myModel.numPositions; i++) // Loop through all the positions (really really inefficient I know (will have to change!))
      {
        // Check hash table for values:
        for (unsigned int a = 0; a < myModel.numPositions; a++)
        {
          for (unsigned int b = 1; b < myModel.numPositions; b++)
          {
            if (i == HashTable[a][b]) {skipVal = true; break; std::cout << "match" << std::endl; }
            std::cout << "i: " << i << "\t" << "a: " << a << "\t" << "b: " << b << "\t" << "HashTable: " << HashTable[a][b] << std::endl;
          }
          if(skipVal) { break; }
        }
        if (!skipVal)
        {
          HashTable[i][0] = i;
          for (unsigned int j = 0; j < myModel.numPositions; j++)
          {
              if ((i != j) && (myModel.positions[i] == myModel.positions[j])){ HashTable[i][count] = j; count++; }
          }
        }
        count = 1;
        skipVal = false;
      }

      //  Take first colume of hash table as they are the unique values.
      myModel.indices.push_back(0); // first position is always unique
      for (unsigned int i = 1; i < myModel.numPositions; i++)
      {
        if(HashTable[i][0] > 0) {myModel.indices.push_back(HashTable[i][0]);} // Unsure no unpopulated indexs are included.
      }
      std::cout << "HASHTABLE RESULT: " << std::endl;
      for (unsigned int i = 0; i < myModel.numPositions; i++)
      {
        for (unsigned int j = 0; j < myModel.numPositions; j++)
        {
          std::cout << HashTable[i][j] << "   ";
        }
        std::cout << std::endl;
      }
      */
      // Redraw faccets:
      /*
      unsigned int count = 0;
      for (unsigned int i = 0; i < myModel.indices.size(); i++)
      {
        myModel.positions[i] = myModel.positions[myModel.indices[i]];
        myModel.normals[i] = myModel.normals[myModel.indices[i]];
        myModel.texCoords[i] = myModel.texCoords[myModel.indices[i]];
      }
      myModel.positions.erase(myModel.indices.size(), myModel.positions.size());
      myModel.normals.erase(myModel.indices.size(), myModel.normals.size());
      myModel.texCoords.erase(myModel.indices.size(), myModel.texCoords.size());
      */


  } // end of else file opened..
  file.close();
}



void readAsciiSTL(const std::string& STLfileName, model& myModel) // Read ASCII file and store in model parameters:
{
  // Wait until way down the track.....
}
