#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../model/model.h"

class mesh
{
public:
	mesh(const model& meshModel);

	void draw(unsigned int TYPE); // this will allow to select either points or trables:

	virtual ~mesh();
protected:
private:
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
