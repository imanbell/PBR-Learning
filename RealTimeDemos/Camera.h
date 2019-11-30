#pragma once

#include <glm\glm\glm.hpp>
#include <glm\glm\matrix.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm\glm\gtx\quaternion.hpp>

#include "VisuUtils.h"

#include <iostream>

struct Plane {
	glm::vec3 normal;
	float constant;
	void setValuesAndNormalize(float iNx, float iNy, float iNz, float iC) {
		normal.x = iNx;
		normal.y = iNy;
		normal.z = iNz;
		constant = iC;
		float inverseNormalLength = 1.0f / glm::length(normal);
		normal = inverseNormalLength*normal;
		constant *= inverseNormalLength;
	}
};

struct Frustum {
	Plane _planes[6];
	void setFromViewProjectionMatrix(glm::mat4& iViewProjectionMatrix) {
		float* me = glm::value_ptr(iViewProjectionMatrix);
		float me0 = me[0];
		float me1 = me[1];
		float me2 = me[2];
		float me3 = me[3];
		float me4 = me[4];
		float me5 = me[5];
		float me6 = me[6];
		float me7 = me[7];
		float me8 = me[8];
		float me9 = me[9];
		float me10 = me[10];
		float me11 = me[11];
		float me12 = me[12];
		float me13 = me[13];
		float me14 = me[14];
		float me15 = me[15];
		_planes[0].setValuesAndNormalize(me3 - me0, me7 - me4, me11 - me8, me15 - me12);
		_planes[1].setValuesAndNormalize(me3 + me0, me7 + me4, me11 + me8, me15 + me12);
		_planes[2].setValuesAndNormalize(me3 + me1, me7 + me5, me11 + me9, me15 + me13);
		_planes[3].setValuesAndNormalize(me3 - me1, me7 - me5, me11 - me9, me15 - me13);
		_planes[4].setValuesAndNormalize(me3 - me2, me7 - me6, me11 - me10, me15 - me14);
		_planes[5].setValuesAndNormalize(me3 + me2, me7 + me6, me11 + me10, me15 + me14);
	}

	bool isCulled(BoundingSphere& iBS) {
		glm::vec3& center = iBS.center;
		float negRadius = -iBS.radius;
		for (char i = 0; i < 6; i++) {
			float distance = glm::dot(_planes[i].normal, center) + _planes[i].constant;
			if (distance < negRadius) {
				return true;
			}
		}
		return false;
	}
};


class Camera
{
private:
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;

	glm::vec3 _position;	
	glm::vec3 _target;
	glm::vec3 _upVector;
	float _fov;//in degrees
	float _near;
	float _far;
	float _aspectRatio;
	glm::vec3 _positionToTarget;

	Frustum _frustum;
	
public:
	Camera();

	void setAspectRatio(float iAspectRatio);
	void updateProjectionMatrix();
	glm::mat4& getProjectionMatrix();
	void updateViewMatrix();
	glm::mat4& getViewMatrix();
	glm::vec3& getPosition();
	void updateFrustum();
	bool isCulled(BoundingSphere& iBS);
	void reframeToBSphere(BoundingSphere& iBoundingSphere);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
	{
		
		float angle = glm::length(glm::vec3(xoffset, yoffset, 0.0));
		_positionToTarget = _target - _position;
		glm::vec3 eyeDirection = glm::normalize(-_positionToTarget);
		glm::vec3 up = glm::normalize(_upVector);
		glm::vec3 side = glm::normalize(glm::cross(up, eyeDirection));
		
		up = yoffset*up;
		side = xoffset*side;
		
		glm::vec3 moveDirection = up + side;
		
		glm::vec3 axis = glm::normalize(glm::cross(moveDirection, -_positionToTarget));
		
		glm::quat quaternion = glm::angleAxis(angle, axis);

		_positionToTarget = quaternion*_positionToTarget;
		_upVector = quaternion*_upVector;
		_position = _target - _positionToTarget;
		
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		float factor = 1.0f - 0.1f*yoffset;
		if (factor != 1.0f && factor > 0.0) {
			_positionToTarget = factor*_positionToTarget;
			_position = _target - _positionToTarget;
		}
	}

	~Camera();
};

