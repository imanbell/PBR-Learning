#pragma once
#include "IdCounters.h"
#include "Program.h"

struct MaterialStruct{};

class Material
{
protected:
	unsigned int _offsetInUBO;
private:
	int id;
	const char* _vertexShader;
	const char* _fragmentShader;
	std::string _vertexShaderCode;
	std::string _fragmentShaderCode;
	Program* _program;
	MaterialStruct _materialParameters;
public:
	Material();
	int getId();
	void setShaders(std::string& iVertexShader, std::string& iFragmentShader);
	void setShaderBodiesFromFiles(const char* iVertexPath, const char* iFragmentPath);
	void createProgram();
	int getShaderProgram();
	Program* getProgram();
	virtual void initUBO(GLuint& iBindingPoint);
	virtual void updateUBO();
	virtual bool isPBR();
	void setOffsetInUBO(unsigned int iOffsetInUBO);
	unsigned int getOffsetInUBO();
	virtual MaterialStruct& getParametersStruct() = 0;
	~Material();
};

