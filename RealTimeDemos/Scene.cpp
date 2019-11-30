#include "Scene.h"

Scene::Scene()
{
}

void Scene::addMesh(Mesh* iMesh)
{
	_meshes.push_back(iMesh);
}

void Scene::addLight(Light* iLight)
{
	_lights.push_back(iLight);
}

std::vector<Mesh*> Scene::getMeshes()
{
	return _meshes;
}

 std::vector<Light*> Scene::getLights()
{
	return _lights;
}

void Scene::deleteScene() {

}

Scene::~Scene()
{
}
