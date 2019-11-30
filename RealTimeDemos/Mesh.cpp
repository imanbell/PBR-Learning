#include "Mesh.h"



Mesh::Mesh()
{//not used
}

Mesh::Mesh(Geometry* iGeometry, Material* iMaterial)
{
	id = __idCounter_Mesh++;
	_geometry = iGeometry;
	_material = iMaterial;
	_bSphere = iGeometry->getBoundingSphere();
}


BoundingSphere& Mesh::getBoundingSphere()
{
	return _bSphere;
}

Material* Mesh::getMaterial()
{
	return _material;
}

bool Mesh::VAOIsInitialized() {
	return _geometry->VAOIsInitialized();
}

Geometry* Mesh::getGeometry()
{
	return _geometry;
}

void Mesh::setModelMatrix(glm::mat4 &iModelMatrix) {
	_modelMatrix = iModelMatrix;
	_bSphere.applyTransformation(_modelMatrix);
}

void Mesh::deleteMesh() {
	_geometry->deleteGeometry();
};

Mesh::~Mesh()
{
	//delete _geometry;
}
