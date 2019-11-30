#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class VertexArrayObject
{
private:
	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _EBO;
public:	
	VertexArrayObject();
	void init(float* iAttributeArray, unsigned int* iIndexArray, unsigned int nbVertices, unsigned int iNbIndices, unsigned int iNbFloatsPerVertex);
	int getVAO();
	void deleteBuffers();
	~VertexArrayObject();
};

