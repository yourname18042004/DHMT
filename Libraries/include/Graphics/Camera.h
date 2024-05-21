#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include "Camera.h"
#include "ShaderClass.h"

class Camera
{
	private:
		glm::vec3 Position;
		glm::vec3 Orientation;
		glm::vec3 Up;
		glm::mat4 viewMatrix;

		int* width;
		int* height;

		bool firstClick = true;
		bool follow = false;

		float speed;
		float sensitivity;
	public:
		Camera(int* wight, int* height, glm::vec3 position);

		void updateMatrix(float FOVdeg, float nearPlane, float farPlane, Shader shader, const char* uniform);
		glm::vec3 getPosititon();
		glm::vec3 getOr() { return Orientation; }
		void Inputs(GLFWwindow* window, float dt);
};

#endif // !CAMERA_CLASS_H
