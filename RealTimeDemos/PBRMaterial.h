#pragma once
#include "Material.h"
#include <glm\glm\glm.hpp>
#include "UBO.h"

struct PBRStruct : public MaterialStruct {
	glm::vec3 albedo;
	float roughness;
	float metallic;
	float ao;
};

class PBRMaterial :
	public Material
{
private:
	PBRStruct _pbrStruct;
	UBO _pbrUBO;
	bool _updateUBO;
	bool _UBOInitialized;

public:
	PBRMaterial();
	void setAlbedo(glm::vec3& iAlbedo);
	void setRoughness(float iRoughness);
	void setMetallic(float iMetallic);
	void setAO(float iAO);
	void initUBO(GLuint& iBindingPoint);
	void updateUBO();
	bool isPBR();
	PBRStruct& getParametersStruct();
	~PBRMaterial();
};

