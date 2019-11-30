#include "VertexArrayObject.h"


VertexArrayObject::VertexArrayObject()
{
	_VAO = -1;
	_VBO = -1;
	_EBO = -1;
}

void VertexArrayObject::init(float* iAttributeArray, unsigned int* iIndexArray, unsigned int iNbVertices, unsigned int iNbIndices, unsigned int iNbFloatsPerVertex)
{
	GLuint pLoc = 0;
	GLuint nLoc = 1;
	GLuint cLoc = 2;

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(iAttributeArray)*iNbVertices*iNbFloatsPerVertex, iAttributeArray, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iIndexArray)*iNbIndices, iIndexArray, GL_STATIC_DRAW);


	unsigned int byteOffset = 0;
	glVertexAttribPointer(pLoc, 3, GL_FLOAT, GL_FALSE, iNbFloatsPerVertex * sizeof(float), BUFFER_OFFSET(byteOffset));
	glEnableVertexAttribArray(pLoc);
	byteOffset += 12;

	glVertexAttribPointer(nLoc, 3, GL_FLOAT, GL_FALSE, iNbFloatsPerVertex * sizeof(float), BUFFER_OFFSET(byteOffset));
	glEnableVertexAttribArray(nLoc);
	byteOffset += 12;

	glVertexAttribPointer(cLoc, 3, GL_FLOAT, GL_FALSE, iNbFloatsPerVertex * sizeof(float), BUFFER_OFFSET(byteOffset));
	glEnableVertexAttribArray(cLoc);
	byteOffset += 12;

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	_VAO = VAO;
	_VBO = VBO;
	_EBO = EBO;
}

int VertexArrayObject::getVAO() {
	return _VAO;
}

void VertexArrayObject::deleteBuffers() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

VertexArrayObject::~VertexArrayObject()
{
}
