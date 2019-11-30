#include "PBRSpheres.h"
#include "SphereGeometry.h"


PBRSpheres::PBRSpheres()
{	
	Material* PBRMaterial = new Material();
	
	PBRMaterial->setShaderBodiesFromFiles(
		"PhysicalMaterial.vs",
		"PhysicalMaterial.fs"
	);

	SphereGeometry* sphereGeometry = new SphereGeometry();
	//creating the mesh
	Mesh* sphereMesh = new Mesh(sphereGeometry, PBRMaterial);

	//creating the light
	Light* light = new Light();
	light->setPosition(glm::vec3(3.0f, 3.0f, 3.0f));
	//creating the scene
	_scene = new Scene();
	_scene->addMesh(sphereMesh);
	_scene->addLight(light);
}


PBRSpheres::~PBRSpheres()
{
}
