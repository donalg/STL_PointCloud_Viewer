#ifndef MODEL_INCLUDED_H
#define MODEL_INCLUDED_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

class model
{
public:
  model(const std::string& fileName); // does nothing but initalise the number of varables:

  std::vector<glm::vec3> positions; // both STL & model - (drawn to mesh)
  std::vector<glm::vec3> normals; // Just STL - (drawn to mesh)
  std::vector<glm::vec2> texCoords; // both STL & model - (drawn to mesh)
	std::vector<unsigned int> indices; // Will be used to reference the ideal
	unsigned int numIndices;
  unsigned int numPositions; // both STL & model
  unsigned int numNormals; // both STL & model

  std::vector<glm::vec3> meshNodes; // Just model;
  unsigned int numMeshNodes; // Just model;

  unsigned int Xmax, Xmin; // Will help determine
  unsigned int Ymax, Ymin;
  unsigned int Zmax, Zmin;

	unsigned int modelType;
  //inline unsigned int getModelType() {return modelType;}              // Save this for later as will help with the drawing of the model (may also have to be user defined)
  virtual ~model();

};

#endif // MODEL_H
