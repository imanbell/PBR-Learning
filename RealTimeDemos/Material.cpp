#include "Material.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderUtils.h"

Material::Material()
{
	id = __idCounter_Material++;
	_program = nullptr;
	_offsetInUBO = -1;
}

int Material::getId()
{
	return id;
}

void Material::setShaders(std::string& iVertexShader, std::string& iFragmentShader) {
	_vertexShaderCode = iVertexShader;
	_fragmentShaderCode = iFragmentShader;
}

void Material::setShaderBodiesFromFiles(const char* iVertexPath, const char* iFragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(iVertexPath);
		fShaderFile.open(iFragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	std::string uniformsStr = std::string(__shaderUniforms);
	std::string vshader = std::string(__vertexShaderPrefix) + std::string("\n\0") + uniformsStr + std::string("\n\0") + vertexCode;
	std::string fshader = std::string(__fragmentShaderPrefix) + std::string("\n\0") + uniformsStr + std::string("\n\0") + fragmentCode;

	setShaders(vshader, fshader);
}

void Material::createProgram() {
	if (_program == nullptr) {
		_program = new Program();
		_program->initProgram(_vertexShaderCode, _fragmentShaderCode);
	}	
}

int Material::getShaderProgram() {
	return _program->getShaderProgram();
}

Program* Material::getProgram() {
	return _program;
}

void Material::initUBO(GLuint& iBindingPoint) {}
void Material::updateUBO() {}

bool Material::isPBR() {
	return false;
}

void Material::setOffsetInUBO(unsigned int iOffsetInUBO) {
	_offsetInUBO = iOffsetInUBO;
}

unsigned int Material::getOffsetInUBO() {
	return _offsetInUBO;
}

//MaterialStruct& Material::getParametersStruct() { return _materialParameters; }

Material::~Material()
{
}

