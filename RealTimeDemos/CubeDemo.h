#pragma once
#include "Demo.h"
class CubeDemo :
	public Demo
{
private:
	Scene* _scene;
	void _createScene();
public:
	CubeDemo();
	Scene* getScene();
	~CubeDemo();
};

