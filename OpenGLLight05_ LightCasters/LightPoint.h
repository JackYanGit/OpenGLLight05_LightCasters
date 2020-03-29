#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class LightPoint
{
public:
	glm::vec3 postion;
	glm::vec3 angles;
	glm::vec3 direction;
	glm::vec3 color;

	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));

	float constant;
	float linear;
	float quadratic;
};

