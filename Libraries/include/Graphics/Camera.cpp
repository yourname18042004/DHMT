#include "Camera.h"


Camera::Camera(int* width, int* height, glm::vec3 position) 
{
	this->width = width;
	this->height = height;
	Position = position;
	Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	speed = 0.1f;
	sensitivity = 100.0f;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane, Shader shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)*width / (float)*height, nearPlane, farPlane);

	viewMatrix = projection * view;

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(viewMatrix));
}


glm::vec3 Camera::getPosititon()
{
	return Position;
}

void Camera::Inputs(GLFWwindow* window, float dt) 
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += glm::vec3(speed ) * Orientation * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += glm::vec3(speed / 1) * -glm::normalize(glm::cross(Orientation, Up)) * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += glm::vec3(speed / 1) * -Orientation * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += glm::vec3(speed / 1) * glm::normalize(glm::cross(Orientation, Up)) * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += glm::vec3(speed / 1) * Up * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Position += glm::vec3(speed / 1) * -Up * dt;
	}
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) follow = true;
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) follow = false;

	if (follow) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			// dua con tro chuot vao chinh giua cua so
			glfwSetCursorPos(window, (*width / 2), (*height / 2));
			firstClick = false;
		}

		double mouseX, mouseY;

		// lay vi tri con tro chuot
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// do lech giua con tro va chinh giua man hinh la goc quay cua vector dinh huong (Orientation)
		float rotY = sensitivity * (float)(mouseY - (*height / 2)) / *height;
		float rotX = sensitivity * (float)(mouseX - (*width / 2)) / *width;

		// quay vector dinh huong(Orientation) mot goc rotY quanh truc vuong goc voi vector dinh huong (Orientation) va vector up
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotY), glm::normalize(glm::cross(Orientation, Up)));

		// gioi han goc quay 
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
			Orientation = newOrientation;
		}
		
		// quay vector dinh huong(Orientation) mot goc rotX quanh truc vuong goc voi vector up
		Orientation = glm::rotate(Orientation, glm::radians(-rotX), Up);
		
		// dua con tro chuot vao chinh giua cua so
		glfwSetCursorPos(window, (*width / 2), (*height / 2));

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !follow)
	{
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}
