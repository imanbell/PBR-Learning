#include "UBO.h"
#include "IdCounters.h"

UBO::UBO()
{
	_glID = -1;
}

void UBO::init(GLsizeiptr iSizeOfUBO, GLvoid* iUBOStruct, GLuint iBindingPoint)
{
	glGenBuffers(1, &_glID);
	glBindBuffer(GL_UNIFORM_BUFFER, _glID);
	glBufferData(GL_UNIFORM_BUFFER, iSizeOfUBO, iUBOStruct, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, iBindingPoint, _glID);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void UBO::update(GLsizeiptr iSizeOfUBO, GLvoid* iUBOStruct) {
	glBindBuffer(GL_UNIFORM_BUFFER, _glID);
	GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	memcpy(p, iUBOStruct, iSizeOfUBO);
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UBO::~UBO()
{
}
