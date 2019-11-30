#pragma once


#include <glm\glm\glm.hpp>
#include <glm\glm\matrix.hpp>
#include <glm\glm\gtc\type_ptr.hpp>


#include <glm\glm\gtx\norm.hpp>

struct BoundingSphere {
	glm::vec3 center;
	float radius;
	void applyTransformation(glm::mat4& iTransformation) {
		glm::vec3 scaleSq = 
			glm::vec3(
				glm::length2(glm::vec3(iTransformation[0])),
				glm::length2(glm::vec3(iTransformation[1])),
				glm::length2(glm::vec3(iTransformation[2])));
		float maxScaleSq = glm::max(scaleSq.x, glm::max(scaleSq.y, scaleSq.z));
		float scale = sqrt(maxScaleSq);
		radius *= scale;
		center = glm::vec3(iTransformation*glm::vec4(center, 1.0));
	}

	void mergeWithSphere(BoundingSphere& iBoundingSphere) {

		BoundingSphere bigger = iBoundingSphere;
		BoundingSphere smaller = iBoundingSphere;
		float maxRadius;
		float minRadius;
		if (iBoundingSphere.radius > radius) {
			maxRadius = bigger.radius;
			smaller.center = center;
			smaller.radius = radius;
			minRadius = radius;
		} else {
			bigger.center = center;
			bigger.radius = radius;
			maxRadius = radius;
			minRadius = smaller.radius;
		}

		float centerToCenterLength = (float)glm::distance(center, iBoundingSphere.center);
		//float centerToCenterLength = (float)((iBoundingSphere.center - center).length());
		
		//if one sphere inside the other
		if (centerToCenterLength <= (maxRadius - minRadius)) {
			center = bigger.center;
			radius = bigger.radius;
			return;
		}

		glm::vec3 cToCVector = glm::normalize(bigger.center - smaller.center);

		//if they intersect
		if (centerToCenterLength < (maxRadius + minRadius)) {
			radius = 0.5f*(centerToCenterLength + maxRadius + minRadius);
		} else {//if they don't intersect
			radius = maxRadius + minRadius;
		}
		glm::vec3 pointS = smaller.center - cToCVector*minRadius;
		glm::vec3 pointB = bigger.center + cToCVector*maxRadius;
		center = (pointS + pointB)/2.0f;
	}
};
