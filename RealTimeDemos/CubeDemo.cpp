#include "CubeDemo.h"

#include "PBRMaterial.h"

CubeDemo::CubeDemo()
{
	_scene = nullptr;
	_createScene();
}

void CubeDemo::_createScene() {
	//creating the geometry
	Geometry* cubeGeometry = new Geometry();
	std::vector<float> positions = { 
		//face 0 (bottom)
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		//face 1 (top)
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		//face 2 (right)
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, 0.5f,
		-0.5f,  -0.5f, 0.5f, 
		//face 3 (left)
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  -0.5f, 0.5f,
		//face 4 (front)
		-0.5f, -0.5f, -0.5f,
		0.5f,  -0.5f, -0.5f,
		0.5f,  -0.5f, 0.5f,
		-0.5f,  -0.5f, 0.5f,
		//face 5 (back)
		-0.5f, 0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f
};
	std::vector<float> normals = { 
		//face 0
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		//face 1
		0.0f, 0.0f, +1.0f,
		0.0f, 0.0f, +1.0f,
		0.0f, 0.0f, +1.0f,
		0.0f, 0.0f, +1.0f,
		//face 2
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		//face 3
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		//face 4
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		//face 5
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	std::vector<float> colors = normals;
	std::vector<unsigned int> indices = {
		0,2,1,
		0,3,2,
		4,5,6,
		4,6,7,
		8,10,9,
		8,11,10,
		12,13,14,
		12,14,15,
		19,17,18,
		19,16,17,
		21,20,23,
		21,23,22
	};

	cubeGeometry->setAttributeArrays(positions, normals, colors, indices);
	cubeGeometry->setPrimitiveType(GL_TRIANGLES);

	//cube material
	PBRMaterial* cubeMaterial = new PBRMaterial();
	cubeMaterial->setAlbedo(glm::vec3(1.0, 0.0, 1.0));
	cubeMaterial->setRoughness(0.2f);
	cubeMaterial->setMetallic(1.0f);
	cubeMaterial->setAO(1.0f);

	//creating the mesh
	Mesh* cubeMesh = new Mesh(cubeGeometry, cubeMaterial);

	//creating the light
	Light* light = new Light();
	light->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	//creating the scene
	_scene = new Scene();
	_scene->addMesh(cubeMesh);
	_scene->addLight(light);
}

Scene* CubeDemo::getScene() {
	return _scene;

}

CubeDemo::~CubeDemo()
{
}
