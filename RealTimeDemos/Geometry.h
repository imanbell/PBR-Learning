#pragma once
#include <vector>
#include "VertexArrayObject.h"

#include "IdCounters.h"
#include "VisuUtils.h"

class Geometry
{
private:

	int id;
	//number of references to this object by meshes
	int _refCount;
	//VBO associated to the geometry
	VertexArrayObject _VAO;
	//index array
	unsigned int* _indexArray;
	//final array to send to the GPU
	float* _attributeArray;
	//primitive type (triangles, lines, points,...)
	unsigned int _primitiveType;
	//nb vertices
	unsigned int _nbVertices;
	//nb indices
	unsigned int _nbIndices;
	//size of vertex (number of floats per vertex)
	unsigned int _sizeOfVertex;

	bool _VAOinitialized;

	BoundingSphere _bSphere;

public:
	Geometry();
	//define the vertex attributes arrays of this geometry
	void setAttributeArrays(
		std::vector<float> iPositions,
		std::vector<float> iNormals,
		std::vector<float> iColors,
		std::vector<unsigned int> iIndices
		);
	BoundingSphere getBoundingSphere();
	void setPrimitiveType(unsigned int iPrimitiveType);
	unsigned int getPrimitiveType();
	unsigned int getNbIndices();
	void initVAO();
	bool VAOIsInitialized();
	VertexArrayObject* getVAO();
	void incRef();
	void decRef();
	void deleteGeometry();
	~Geometry();
};

