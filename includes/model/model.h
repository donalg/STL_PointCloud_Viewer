#ifndef MODEL_H
#define MODEL_#

#include <glm/glm.hpp>
#include <string>
#include <vector>



class model
{
  model(); // does nothing but initalise a black cube... 

  void readSTL(const std::string &STLfileName); // will read either binary or Ascii file types.
  void readModel(const std::string &modelFileName); // will read purely binary file types (model output from computer vision algorithm)
  void readPointCloud(const std::string &pointCloudFileNAme);

  inline glm::vec3 getVertex(unsigned int i) { return vertices[i]; }
  inline glm::vec3 getIndex(unsigned int i) { return indices[i]; }
  inline glm::vec3 getNormal(unsigned int i) { return normals[i]; }
  inline glm::vec2 getTexCoord(unsigned int i) { return texCoords[i]; }
  inline unsigned int getNumVertices() { return numVertices; }
  inline unsigned int getNumIndices() { return numIndices; }
  inline unsigned int getNumMeshNodes() { return numMeshNodes; }

  inline unsigned int getModelType() {return modelType;}

  virtual ~model();

protected:
private:

  enum modelType // To help mesh and shader to deide what to do.
  {
    POINTCLOUD,
    STL,
    MODEL
  };


  std::vector<glm::vec3> vertices; // both STL & model
  std::vector<glm::vec3> indices; // both STL & model
  std::vector<glm::vec3> normals; // Just STL
  std::vector<glm::vec2> texCoords; // both STL & model
  unsigned int numVertices; // both STL & model
  unsigned int numIndices; // both STL & model

  std::vector<glm::vec3> meshNodes; // Just model;
  unsigned int numMeshNodes; // Just model;

};
