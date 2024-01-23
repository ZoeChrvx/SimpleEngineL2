#include "VertexArray.h"
#include <gl/glew.h>

VertexArray::VertexArray(const float* verticesP, unsigned int nbVerticesP, const unsigned int* indicesP, unsigned int nbIndicesP):
	nbVertices(nbVerticesP), nbIndices(nbIndicesP), vertexBuffer(0), indexBuffer(0), vertexArray(0)
{
	//Create vertex array
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	//Create vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, nbVertices * 3.0 * sizeof(float), verticesP, GL_STATIC_DRAW); //Size float == define the size of the stored data

	//Create index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndicesP * sizeof(unsigned int), indicesP, GL_STATIC_DRAW);

	//Specify the vertex attributes
	//(for now, assume one vertex format)
	//Poisition is 3 floats starting at offset 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

VertexArray::~VertexArray() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::setActive() {
	glBindVertexArray(vertexArray);
}
