#pragma once
#include "Scene.h"
#include "Camera.h"
#include "UBO.h"

#include <glm\glm\glm.hpp>
#include <glm\glm\matrix.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

struct FrameStruct {
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 cameraPosition;
};

struct SceneStruct {
	glm::vec3 lightPosition;
};


class Renderer
{
private:
	Renderer();
	void _init();
	void _reframeToScene();
	void _initUBOs();
	void _applyFrustumCulling();
	void _updateFrameUBO();
	void _renderMesh(Geometry* iGeometry);
	Scene* _scene;
	SceneStruct _sceneStruct;
	FrameStruct _frameStruct;
	GLuint _bindingPointCount;
	UBO _frameUBO;
	UBO _sceneUBO;
	UBO _PBRMaterialsUBO;
	Camera _camera;
	BoundingSphere _sceneBSphere;
	std::map<Material*, std::vector<Mesh*> > _afterCullingMeshesPerMaterial;
public:	
	Renderer(Scene* iScene);
	void setViewport(int iWidth, int iHeight);
	Camera& getCamera();
	void render();	
	void deleteScene();
	~Renderer();
};


