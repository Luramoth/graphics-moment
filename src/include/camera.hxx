#include "glm/glm.hpp"

class Camera {
	public:
	//variables
	glm::vec3 pos;

	glm::vec3 target;
	glm::vec3 direction;

	glm::vec3 up;
	glm::vec3 right;

	glm::vec3 camUp;

	//functions
	Camera();
};