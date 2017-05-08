#include "mesh.h"
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../obj_loader/obj_loader.h"


mesh::mesh(const std::string& filename)
{
		IndexedModel model = OBJModel(filename).ToIndexedModel();
		initMesh(model);
}

mesh::mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{

	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].getPos());
		model.texCoords.push_back(*vertices[i].getTexCoord());
		model.normals.push_back(*vertices[i].getNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	initMesh(model);

/*
	//myDrawCount = numVertices;
	myDrawCount = numIndicies;
	glGenVertexArrays(1, &myVertexArrayObject);
	glBindVertexArray(myVertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].getPos());
		texCoords.push_back(*vertices[i].getTexCoord());
	}

	glGenBuffers(NUM_BUFFERS, myVertexArrayBuffers); // Generate buffers to store data in:

	/// Positions: (This is what is read glBindAttribLocation(myProgram, 0, "position"); in sharder.cpp)
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, (numVertices * sizeof(positions[0])), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Texture Coordinates:
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, (numVertices * sizeof(texCoords[0])), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myVertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (numIndicies * sizeof(indicies[0])), &indicies[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
*/
}


void mesh::initMesh(const IndexedModel& model)
{

	myDrawCount = model.indices.size();

	glGenVertexArrays(1, &myVertexArrayObject);
	glBindVertexArray(myVertexArrayObject);

	glGenBuffers(NUM_BUFFERS, myVertexArrayBuffers); // Generate buffers to store data in:

	/// Positions: (This is what is read glBindAttribLocation(myProgram, 0, "position"); in sharder.cpp)
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, (model.positions.size() * sizeof(model.positions[0])), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Texture Coordinates:
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, (model.positions.size() * sizeof(model.texCoords[0])), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, (model.normals.size() * sizeof(model.normals[0])), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myVertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (model.indices.size() * sizeof(model.indices[0])), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}



mesh::~mesh()
{
	glDeleteBuffers(NUM_BUFFERS, myVertexArrayBuffers);
	glDeleteVertexArrays(1, &myVertexArrayObject);
}

void mesh::draw()
{
	glBindVertexArray(myVertexArrayObject);
	//glDrawArrays(GL_TRIANGLES, 0, myDrawCount);
	glDrawElements(GL_TRIANGLES, myDrawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
