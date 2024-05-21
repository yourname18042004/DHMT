#include "Display.h"

Display::Display(){}

Display::Display(int width, int height) 
{
	this->WIDTH		= width;
	this->HEIGHT	= height;
	Init();
}

Display::~Display(){}

void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight)
{
	std::cout << newWidth << " " << newHeight << "\n";
}
void Display::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwWindowHint(GLFW_SAMPLES, 32); 

	//glfwWindowHint(GLFW_DECORATED, NULL); 
	
	GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor(); 

	const GLFWvidmode* mode = glfwGetVideoMode(MyMonitor);
	WIDTH = mode->width * 0.8;
	HEIGHT = mode->height * 0.8;

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "opengl", NULL, NULL); // glfwGetPrimaryMonitor()
	glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
	glfwSetWindowSizeCallback(window, window_reshape_callback);

	if (window == NULL)
	{
		std::cout << "khong tao duoc cua so" << std::endl;
		glfwTerminate();
		return;
	}

	// chi dinh cua so hien tai dang su dung
	glfwMakeContextCurrent(window);

	// load Glad de cau hinh cho OpenGL
	gladLoadGL();

	// chi dinh che do xem của OpenGL cua so
	glViewport(0, 0, WIDTH, HEIGHT);
}
void Display::Loop()
{
	while (!(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) && !glfwWindowShouldClose(window))
	{
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "Thanh Giap Kien" + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;

			// Use this if you have disabled VSync
			//camera.Inputs(window);
		}

		glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
		glViewport(0, 0, WIDTH, HEIGHT);

		Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Display::Draw()
{
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Display::Delete()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
