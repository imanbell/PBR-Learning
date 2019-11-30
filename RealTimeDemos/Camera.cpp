#include "Camera.h"
Camera::Camera()
{
	_fov = 45.0f;
	_near = 0.1f;
	_far = 100.0f;
	_aspectRatio = 800.0f/600.0f;
	_position = glm::vec3(0.0, 0.0, 0.0);
	_target = glm::vec3(0.0, 0.0, 0.0);
	_upVector = glm::vec3(0.0, 1.0, 0.0);
	_positionToTarget = _target - _position;
}

void Camera::reframeToBSphere(BoundingSphere& iBoundingSphere) {
	_target = iBoundingSphere.center;
	glm::vec3 lookAtVector = glm::normalize(glm::vec3(-1.0, -1.0, -1.0));
	float distanceToTarget = iBoundingSphere.radius*1.5f;
	_position = _target - lookAtVector*distanceToTarget;
	_upVector = glm::normalize(glm::vec3(-1.0, -1.0, 1.0));
	_positionToTarget = _target - _position;
}

void Camera::setAspectRatio(float iAspectRatio) {
	_aspectRatio = iAspectRatio;
}

void Camera::updateProjectionMatrix() {
	_projectionMatrix = glm::perspective(glm::radians(_fov), _aspectRatio, _near, _far);
}

glm::mat4& Camera::getProjectionMatrix() {
	return _projectionMatrix;
}

void Camera::updateViewMatrix() {
	
	_viewMatrix = glm::lookAt(_position, _target, _upVector);
}

glm::mat4& Camera::getViewMatrix() {
	return _viewMatrix;
}

glm::vec3& Camera::getPosition() {
	return _position;
}

void Camera::updateFrustum() {
	//view and projection matrices are up to date at this point
	glm::mat4 viewProj = _projectionMatrix*_viewMatrix;
	_frustum.setFromViewProjectionMatrix(viewProj);	
}

bool Camera::isCulled(BoundingSphere& iBS) {
	return _frustum.isCulled(iBS);
}

Camera::~Camera()
{
}
