#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Program
{
private:
	int _shaderProgram;
	//unsigned int _frameUBOLocation;
	//unsigned int _sceneUBOLocation;

public:
	Program();
	//void initProgram(const char* iVertexShader, const char* iFragmentShader);
	void initProgram(std::string& iVertexShader, std::string& iFragmentShader);
	int getShaderProgram();
	~Program();
};

