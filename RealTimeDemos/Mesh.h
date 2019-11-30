
#include "Geometry.h"
#include "Material.h"
#include "IdCounters.h"

#include <glm\glm\glm.hpp>
#include <glm\glm\matrix.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

#include "VisuUtils.h"

class Mesh
{
protected:
	Geometry* _geometry;
	Material* _material;

private:
	Mesh();
	int id;
	glm::mat4 _modelMatrix;
	BoundingSphere _bSphere;
public:
	Mesh(Geometry* iGeometry, Material* iMaterial);
	BoundingSphere& getBoundingSphere();
	Material* getMaterial();
	Geometry* getGeometry();
	void setModelMatrix(glm::mat4 &iModelMatrix);
	bool VAOIsInitialized();
	void deleteMesh();
	~Mesh();
};

