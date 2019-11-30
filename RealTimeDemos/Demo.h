#pragma once
#include "Scene.h"

class Demo
{
protected:
	Scene* _scene;
public:
	Demo();
	Scene* getScene();
	~Demo();
};

