#include "PBRMaterial.h"


PBRMaterial::PBRMaterial()
{
	setShaderBodiesFromFiles(
		"PhysicalMaterial.vs",
		"PhysicalMaterial.fs"
	);
	_updateUBO = true;
	_UBOInitialized = false;

}

void PBRMaterial::setAlbedo(glm::vec3& iAlbedo) {
	_pbrStruct.albedo = iAlbedo;
	_updateUBO = true;
}

void PBRMaterial::setRoughness(float iRoughness) {
	_pbrStruct.roughness = iRoughness;
	_updateUBO = true;
}

void PBRMaterial::setMetallic(float iMetallic) {
	_pbrStruct.metallic = iMetallic;
	_updateUBO = true;
}

void PBRMaterial::setAO(float iAO) {
	_pbrStruct.ao= iAO;
	_updateUBO = true;
}

void PBRMaterial::initUBO(GLuint& iBindingPoint) {
	if (!_UBOInitialized) {
		_pbrUBO.init(sizeof(_pbrStruct), &_pbrStruct, iBindingPoint++);
		_UBOInitialized = true;
	}
}

void PBRMaterial::updateUBO() {
	if (_updateUBO)
		_pbrUBO.update(sizeof(_pbrStruct), &_pbrStruct);
}

PBRStruct& PBRMaterial::getParametersStruct() {
	return _pbrStruct;
}

bool PBRMaterial::isPBR() {
	return true;
}

PBRMaterial::~PBRMaterial()
{
}
