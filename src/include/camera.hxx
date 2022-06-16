#pragma once

#include "glm/glm.hpp"
#include "shader.hxx"

class Camera {
	private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	public:
	//vars
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float cameraSpeed = 2.5f;

	float pitch, yaw;

	//functions
	Camera(Shader shader);

	void update();
};