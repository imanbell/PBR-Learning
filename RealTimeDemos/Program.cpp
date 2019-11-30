#include "Program.h"
#include <iostream>


Program::Program()
{
	_shaderProgram = -1;
}

//void Program::initProgram(const char* iVertexShader, const char* iFragmentShader) {
void Program::initProgram(std::string& iVertexShader, std::string& iFragmentShader) {
	const char* vshader = iVertexShader.c_str();
	const char* fshader = iFragmentShader.c_str();

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vshader, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fshader, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);
	// check for linking errors
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//retrieve block binding ids
	GLuint bindingPointScene = 0;
	// get index of uniform buffer from shader
	GLuint blockIndexScene = glGetUniformBlockIndex(_shaderProgram, "sceneUBO");
	// bind uniform block to binding point
	glUniformBlockBinding(_shaderProgram, blockIndexScene, bindingPointScene);

	//retrieve block binding ids
	GLuint bindingPointFrame = 1;
	// get index of uniform buffer from shader
	GLuint blockIndexFrame = glGetUniformBlockIndex(_shaderProgram, "frameUBO");
	// bind uniform block to binding point
	glUniformBlockBinding(_shaderProgram, blockIndexFrame, bindingPointFrame);

	//retrieve block binding ids
	GLuint bindingPointPBR = 2;
	// get index of uniform buffer from shader
	GLuint blockIndexPBR = glGetUniformBlockIndex(_shaderProgram, "PBR_UBO");
	// bind uniform block to binding point
	glUniformBlockBinding(_shaderProgram, blockIndexPBR, bindingPointPBR);

	//retrieve block binding ids
	GLuint bindingPointPBRGlobal = 3;
	// get index of uniform buffer from shader
	GLuint blockIndexPBRGlobal = glGetUniformBlockIndex(_shaderProgram, "PBR_Global_UBO");
	// bind uniform block to binding point
	glUniformBlockBinding(_shaderProgram, blockIndexPBRGlobal, bindingPointPBRGlobal);

}

int Program::getShaderProgram() {
	return _shaderProgram;
}

Program::~Program()
{
}
