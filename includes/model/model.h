#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

struct vertex // Copied from mesh.h this will allow for easier compatibility:
{
public:
	vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* getTexCoord() { return &texCoord; }
	inline glm::vec3* getNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class model
{
public:

  model(); // does nothing but initalise the number of varables:

  void readSTL(const std::string &STLfileName);                // will read either binary or Ascii file types.
        // Will also initalise the model type relating to STL files thus locking curtin variable access
  void readModel(const std::string &modelFileName);            // will read purely binary file types (model output from computer vision algorithm)
        // Will also initalise the model type relating to model files thus locking curtin variable access
  void readPointCloud(const std::string &pointCloudFileNAme);  // will allow to read in point clouds
        // Will also initalise the model type relating to Point Clouds files thus locking curtin variable access

  std::vector<vertex> vertices; // stores all the information
  std::vector<glm::vec3> positions; // both STL & model - (drawn to mesh)
  std::vector<vertex> indices; // both STL & model - is a refinement of the verticies (will allow for the information to be drawn)
  std::vector<glm::vec3> normals; // Just STL - (drawn to mesh)
  std::vector<glm::vec2> texCoords; // both STL & model - (drawn to mesh)
  unsigned int numPositions; // both STL & model
  unsigned int numVertices;
  unsigned int numIndices; // both STL & model
  unsigned int numNormals; // both STL & model

  std::vector<glm::vec3> meshNodes; // Just model;
  unsigned int numMeshNodes; // Just model;

  unsigned int Xmax, Xmin; // Will help determine
  unsigned int Ymax, Ymin;
  unsigned int Zmax, Zmin;

  //inline unsigned int getModelType() {return modelType;}              // Save this for later as will help with the drawing of the model (may also have to be user defined)

  virtual ~model();

protected:
private:
  void readBinarySTL(const std::string& STLfileName);
  vertex tempVertex;

};

#endif // MODEL_H
