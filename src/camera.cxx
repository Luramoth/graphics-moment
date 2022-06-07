#include "include/camera.hxx"

#include "include/glm/ext/matrix_transform.hpp"
#include "include/glm/fwd.hpp"
#include "include/glm/geometric.hpp"

Camera::Camera(){
	//set vars
	Camera::pos = glm::vec3(0.0f,0.0f,3.0f);

	Camera::target = glm::vec3(0.0f, 0.0f, 0.0f);
	Camera::direction = glm::normalize(Camera::pos - Camera::target);

	Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera::right = glm::normalize(glm::cross(Camera::up, Camera::direction));

	Camera::camUp = glm::cross(Camera::direction, Camera::right);

	Camera::view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}