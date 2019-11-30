#pragma once
#include <vector>
#include <map>
#include "Mesh.h"
#include "Light.h"

class Scene
{
private:
	std::vector<Mesh*> _meshes;
	std::vector<Light*> _lights;
public:
	Scene();
	void addMesh(Mesh* iMesh);
	void addLight(Light* iLight);
	std::vector<Mesh*> getMeshes();
	std::vector<Light*> getLights();
	void deleteScene();
	~Scene();
};

