#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class UBO
{
private:
	GLuint _glID;
public:
	UBO();
	void init(GLsizeiptr iSizeOfUBO, GLvoid* iUBOStruct, GLuint iBindingPoint);
	void update(GLsizeiptr iSizeOfUBO, GLvoid* iUBOStruct);
	~UBO();
};

