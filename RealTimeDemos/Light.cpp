#include "Light.h"


Light::Light()
{
}

glm::vec3& Light::getPosition() {
	return _position;
}

void Light::setPosition(glm::vec3& iPosition) {
	_position = iPosition;
}

Light::~Light()
{
}
