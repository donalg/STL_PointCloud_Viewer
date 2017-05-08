#include "mesh.h"
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <vector>

mesh::mesh(const model& meshModel)
{

	myDrawCount = meshModel.indices.size(); // size of indicies.

	glGenVertexArrays(1, &myVertexArrayObject);
	glBindVertexArray(myVertexArrayObject);

	glGenBuffers(NUM_BUFFERS, myVertexArrayBuffers); // Generate buffers to store data in:

	/// Positions: (This is what is read glBindAttribLocation(myProgram, 0, "position"); in sharder.cpp)
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, (meshModel.positions.size() * sizeof(meshModel.positions[0])), &meshModel.positions[0], GL_STATIC_DRAW); // This should be fine
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Texture Coordinates:
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, (meshModel.positions.size() * sizeof(meshModel.texCoords[0])), &meshModel.texCoords[0], GL_STATIC_DRAW);  // this should also be fine
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Normals (will have to determine is this is needed for all values)
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, (meshModel.normals.size() * sizeof(meshModel.normals[0])), &meshModel.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

mesh::~mesh()
{
	glDeleteBuffers(NUM_BUFFERS, myVertexArrayBuffers);
	glDeleteVertexArrays(1, &myVertexArrayObject);
}

////////////////////////////////////// Draw the mesh in required format:
void mesh::draw(unsigned int TYPE)
{
	glBindVertexArray(myVertexArrayObject);
	//glDrawElements(GL_TRIANGLES, myDrawCount, GL_UNSIGNED_INT, 0);

	switch(TYPE){
		case 0: // Triangles:
						glDrawArrays(GL_TRIANGLES, 0, myDrawCount);
		case 1: // Lines:
						glDrawArrays(GL_LINES, 0, myDrawCount);
		case 2: // Points
						glDrawArrays(GL_POINTS, 0, myDrawCount);
	}
	glBindVertexArray(0);
}
