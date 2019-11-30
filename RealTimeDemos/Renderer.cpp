#include "Renderer.h"
#include <iostream>
#include "PBRMaterial.h"


Renderer::Renderer()
{//not used
}

Renderer::Renderer(Scene* iScene)
{
	_scene = iScene;
	_bindingPointCount = 0;
	_init();
}

void Renderer::_init() {
	_reframeToScene();
	_initUBOs();
	glEnable(GL_DEPTH_TEST);
}

void Renderer::setViewport(int iWidth, int iHeight) {
	float aspectRatio = (float)iWidth / (float)iHeight;
	_camera.setAspectRatio(aspectRatio);
}

Camera& Renderer::getCamera() {
	return _camera;
}

void Renderer::_initUBOs() {
	
	//scene UBO
	_sceneUBO.init(sizeof(_sceneStruct), &_sceneStruct, _bindingPointCount++);
	_sceneStruct.lightPosition = _scene->getLights()[0]->getPosition();
	_sceneUBO.update(sizeof(_sceneStruct), &_sceneStruct);

	//frame UBO
	_frameUBO.init(sizeof(_frameStruct), &_frameStruct, _bindingPointCount++);

	//materials UBO (only PBR for now) TODO: find a smarter way of doing this
	std::vector<MaterialStruct> PBRStructs;
	std::vector<Mesh*> meshes = _scene->getMeshes();
	int nbMeshes = meshes.size();
	Material* material = nullptr;
	int pbrId = 0;
	for (int i = 0; i < nbMeshes; i++) {
		material = meshes[i]->getMaterial();
		if (material->isPBR()) {
			if (material->getOffsetInUBO() == -1) {
				material->setOffsetInUBO(pbrId++);
				PBRStructs.push_back(material->getParametersStruct());
			}
		}
	}
	//_PBRMaterialsUBO.init(sizeof(PBRStructs), PBRStructs.data(), 3);//sizeof is wrong!!! TODO
	_PBRMaterialsUBO.init(sizeof(PBRStruct)*PBRStructs.size(), PBRStructs.data(), 3);//sizeof is wrong!!! TODO
}

void Renderer::_reframeToScene() {

	std::vector<Mesh*> meshes = _scene->getMeshes();
	int nbMeshes = meshes.size();
	for (int i = 0; i < nbMeshes; i++) {
		_sceneBSphere.mergeWithSphere(meshes[i]->getBoundingSphere());
	}
	_camera.reframeToBSphere(_sceneBSphere);
}


void Renderer::_updateFrameUBO() {
	_frameStruct.cameraPosition = _camera.getPosition();
	_camera.updateViewMatrix();
	_camera.updateProjectionMatrix();
	_frameStruct.viewMatrix = _camera.getViewMatrix();
	_frameStruct.projectionMatrix = _camera.getProjectionMatrix();

	_frameUBO.update(sizeof(_frameStruct), &_frameStruct);
}


void Renderer::_applyFrustumCulling() {

	Mesh* mesh = nullptr;
	Material* material = nullptr;
	bool isCulled = false;
	std::vector<Mesh*> meshes = _scene->getMeshes();
	int nbMeshes = meshes.size();
	for (int i = 0; i < nbMeshes; i++) {
		mesh = meshes[i];
		isCulled = _camera.isCulled(mesh->getBoundingSphere());
		if (!isCulled) {
			material = mesh->getMaterial();
			material->initUBO(_bindingPointCount);
			material->updateUBO();
			_afterCullingMeshesPerMaterial[material].push_back(mesh);
		}
	}
}

void Renderer::render()
{	
	glClearColor(0.878f, 0.878f, 0.878f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//update frame UBO
	_updateFrameUBO();

	//frustum culling
	_applyFrustumCulling();

	std::map<Material*, std::vector<Mesh*> >::iterator itB = _afterCullingMeshesPerMaterial.begin();
	std::map<Material*, std::vector<Mesh*> >::iterator itE = _afterCullingMeshesPerMaterial.end();
	Material* material = nullptr;
	Mesh* mesh = nullptr;

	//loop over the materials
	for (std::map<Material*, std::vector<Mesh*> >::iterator it = itB; it != itE; it++) {
		material = it->first;		
		material->createProgram();
		int shaderProgram = material->getShaderProgram();		
		std::vector<Mesh*> meshes = it->second;
		int nbMeshes = meshes.size();
		glUseProgram(shaderProgram);
		//loop over meshes
		for (int i = 0; i < nbMeshes; i++) {
			mesh = meshes[i];
			bool VAOIsInit = mesh->VAOIsInitialized();
			Geometry* geometry = mesh->getGeometry();
			if (!VAOIsInit) {
				//initialize appropriate buffers				
				geometry->initVAO();
			}
			_renderMesh(geometry);
		}
		glUseProgram(0);
	}
	_afterCullingMeshesPerMaterial.clear();
}


void Renderer::_renderMesh(Geometry* iGeometry) {
	//send object uniforms

	VertexArrayObject* VAO = iGeometry->getVAO();
	unsigned int vao = VAO->getVAO();
	unsigned int primType = iGeometry->getPrimitiveType();
	unsigned int nbIndices = iGeometry->getNbIndices();
	glBindVertexArray(vao); 
	glDrawElements(primType, nbIndices, GL_UNSIGNED_INT, 0);	
	glBindVertexArray(0); // no need to unbind it every time 
}

void Renderer::deleteScene() {
	std::vector<Mesh*> meshes = _scene->getMeshes();
	int nbMeshes = meshes.size();
	for (int i = 0; i < nbMeshes; i++) {
		meshes[i]->deleteMesh();
	}
}


Renderer::~Renderer()
{
}
