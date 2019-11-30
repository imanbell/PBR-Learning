#include "Geometry.h"

Geometry::Geometry()
{
	id = __idCounter_Geometry++;
	_refCount = 0;
	_VAOinitialized = false;
	_attributeArray = nullptr;
	_indexArray = nullptr;
}

void Geometry::setAttributeArrays(
	std::vector<float> iPositions,
	std::vector<float> iNormals,
	std::vector<float> iColors,
	std::vector<unsigned int> iIndices
)
{

	unsigned int positionsSize = iPositions.size();
	if (positionsSize > 0) _sizeOfVertex += 3;
	unsigned int normalsSize = iNormals.size();
	if (normalsSize > 0) _sizeOfVertex += 3;
	unsigned int colorsSize = iColors.size();
	if (colorsSize > 0) _sizeOfVertex += 3;

	
	_nbIndices = iIndices.size();
	_nbVertices = positionsSize / 3;
	unsigned int* indices = new unsigned int[_nbIndices];
	for (unsigned int f = 0; f < _nbIndices; f++) {
		indices[f] = iIndices[f];
	}
	_indexArray = indices;
	

	int arraySize = positionsSize + normalsSize + colorsSize;
	float* array = new float[arraySize];
	int i = 0;
	int p = 0;
	int n = 0;
	int c = 0;
	glm::vec3 _min(INFINITY, INFINITY, INFINITY);
	glm::vec3 _max(-INFINITY, -INFINITY, -INFINITY);
	for (unsigned int f = 0; f < _nbVertices; f++) {
		//positions
		array[i] = iPositions[3*p];
		_min.x = glm::min(iPositions[3 * p], _min.x);
		_max.x = glm::max(iPositions[3 * p], _max.x);
		i++;
		array[i] = iPositions[3*p+1];
		_min.y = glm::min(iPositions[3 * p+1], _min.y);
		_max.y = glm::max(iPositions[3 * p+1], _max.y);
		i++;
		array[i] = iPositions[3*p+2];
		_min.z = glm::min(iPositions[3 * p + 2], _min.z);
		_max.z = glm::max(iPositions[3 * p + 2], _max.z);
		i++;
		p++;
		//normals
		array[i] = iNormals[3*n];
		i++;
		array[i] = iNormals[3*n+1];
		i++;
		array[i] = iNormals[3*n+2];
		i++;
		n++;
		//colors
		array[i] = iColors[3*c];
		i++;
		array[i] = iColors[3*c+1];
		i++;
		array[i] = iColors[3*c+2];
		i++;
		c++;
	}
	_attributeArray = array;

	//compute bounding sphere
	_bSphere.center = (_min + _max)/2.0f;
	_bSphere.radius = 0.5*(_max - _min).length();
}

BoundingSphere Geometry::getBoundingSphere() {
	return _bSphere;
}

void Geometry::setPrimitiveType(unsigned int iPrimitiveType) {
	_primitiveType = iPrimitiveType;
}

unsigned int Geometry::getPrimitiveType() {
	return _primitiveType;
}

unsigned int Geometry::getNbIndices() {
	return _nbIndices;
}

void Geometry::initVAO() {
	_VAO.init(_attributeArray, _indexArray, _nbVertices, _nbIndices, _sizeOfVertex);
	_VAOinitialized = true;
}

bool Geometry::VAOIsInitialized() {
	return _VAOinitialized;
}

VertexArrayObject* Geometry::getVAO() {
	return &_VAO;
}

void Geometry::incRef()
{
	_refCount++;
}

void Geometry::decRef()
{
	_refCount--;
}

void Geometry::deleteGeometry() {
	delete _indexArray;
	delete _attributeArray;
	_VAO.deleteBuffers();
}

Geometry::~Geometry()
{
}
