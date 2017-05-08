#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../obj_loader/obj_loader.h"

struct vertex
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

///////////////////////////////////////////////////////////

class mesh
{
public:
	mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	mesh(const std::string& filename);

	void draw();

	virtual ~mesh();
protected:
private:
	void initMesh(const IndexedModel& model);

	enum
	{
	POSITION_VB,
	TEXCOORD_VB,
	INDEX_VB,
	NORMAL_VB,

	NUM_BUFFERS
	};

	GLuint myVertexArrayObject;
	GLuint myVertexArrayBuffers[NUM_BUFFERS];
	unsigned int myDrawCount;
};

#endif // MESH
