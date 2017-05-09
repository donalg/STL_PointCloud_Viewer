#include "mesh.h"
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <vector>

void drawAxis();

mesh::mesh(const model& meshModel)
{

	myDrawCount =  meshModel.indices.size(); // size of indicies.

	glEnable( GL_PROGRAM_POINT_SIZE );

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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myVertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (meshModel.indices.size() * sizeof(meshModel.indices[0])), &meshModel.indices[0], GL_STATIC_DRAW);

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
						//glDrawArrays(GL_TRIANGLES, 0, myDrawCount);
						glDrawElements(GL_TRIANGLES, myDrawCount, GL_UNSIGNED_INT, 0);
		case 1: // Lines:
						//glDrawArrays(GL_LINES, 0, myDrawCount);
						glDrawElements(GL_LINES, myDrawCount, GL_UNSIGNED_INT, 0);
		case 2: // Points
						//glDrawArrays(GL_POINTS, 0, myDrawCount);

						glDrawElements(GL_POINTS, myDrawCount, GL_UNSIGNED_INT, 0);


						//glDrawArrays(GL_POINTS, 0, myDrawCount);
	}
	drawAxis();
	glBindVertexArray(0);
}

void drawAxis()
{
	// Implement draw axis code here:
	// save previous matrix
glPushMatrix();
// clear matrix
glLoadIdentity();
// apply rotations
//glRotate3f(rotX, 1.0, 0.0, 0.0);
//glRotate3f(rotY, 0.0, 1.0, 0.0);
//glRotate3f(rotZ, 0.0, 0.0, 1.0);
// move the axes to the screen corner
//glTranslatef(-3.0, -2.0, 0.0);
// draw our axes
glBegin(GL_LINES);
//glClear(GL_COLOR_BUFFER_BIT); // Clear ths coloe scheme:
// draw line for x axis
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-1000.0, 0.0, 0.0);
glVertex3f(1000.0, 0.0, 0.0);
// draw line for y axis
glColor3f(1.0, 1.0, 1.0);
glVertex3f(0.0, -1000.0, 0.0);
glVertex3f(0.0, 1000.0, 0.0);
// draw line for Z axis
glColor3f(1.0, 1.0, 1.0);
glVertex3f(0.0, 0.0, -1000.0);
glVertex3f(0.0, 0.0, 1000.0);

//glEnableVertexAttribArray(3);
//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

glEnd();
// load the previous matrix
glPopMatrix();

}
