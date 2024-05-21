#include "DocFile.h"

DocFile::DocFile(std::string filepath, int width, int height)  :
	Display(width, height),
	camera(Camera(&this->WIDTH, &this->HEIGHT, glm::vec3(0, 0, 0))),
	shader(Shader("Shader/Default.vert",
		"Shader/Default.frag"))
{

}

void DocFile::InitObject() 
{
	std::vector<float> VBO;
	std::vector<int> EBO;
	ReadFile().readVBO(VBO, EBO);
	float vertices[] =
	{
		279.4,0, - 181.1,  0.07059, 0.07059, 0.07059,
		-110.4, 0, - 181.1,  0.07059, 0.07059, 0.07059,
		-110.4, 0, - 94.49, 0.07059, 0.07059, 0.07059,
		-188.7, 0, - 94.49,  0.07059, 0.07059, 0.07059,
		-188.7, 0, 255.9, 0.07059, 0.07059, 0.07059,
		279.4, 0, 255.9, 0.07059, 0.07059, 0.07059,
		84.5, 118.1, - 181.1,  0.07059, 0.07059, 0.07059,
		84.5, 118.1, 80.71,  0.07059, 0.07059, 0.07059,
		-188.7, 118.1, 80.71,  0.07059, 0.07059, 0.07059,
		84.5, 118.1, 80.71, 0.07059, 0.07059, 0.07059
		/*-1.0f, -1.0f, 1.0f,		
		1.0f, -1.0f,  1.0f,		
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f*/
	};

	unsigned int indices[] =
	{
		0, 1, 6,  7, 6, 1, 1, 2, 7, 8, 7, 2, 2, 3, 8,
		  3, 4, 8,  9, 8, 4, 4, 5, 9, 6, 9, 5,
		  5, 0, 6, 2, 1, 0, 0, 5, 4, 2, 0, 4,
		  2, 4, 3, 9, 6, 7, 7, 8, 9,
	};

	size = EBO.size();
	std::cout << size << "\n";
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint* vbo = new GLuint[2];
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, VBO.size() * sizeof(float), VBO.data(), GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBO.size()* sizeof(int), EBO.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, vbo);
	glDeleteBuffers(1, &ebo);
}

void DocFile::Draw()
{
	glClearColor(0.6, 0.6, 0.6, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Activate();
	camera.Inputs(window, 100);
	camera.updateMatrix(45, 0.1f, 10000, shader, "View");
	glBindVertexArray(vao);
	
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	glBindTexture(GL_TEXTURE_2D, 0);

}