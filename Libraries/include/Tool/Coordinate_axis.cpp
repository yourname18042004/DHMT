#include "Coordinate_axis.h"
float vertices[] =
{
	0.0f, 0.0f, 0.0f,		0, 1, 1,
	500.0f, 0.0f, 0.0f,		0, 1, 1,
	0.0f, 0.05f, 0.0f,		0, 1, 1,

	0.0f, 0.0f, 0.0f,		1, 0, 1,
	0.0f, 500.0f, 0.0f,		1, 0, 1,
	0.0f, 0.0f, 0.05f,		1, 0, 1,

	0.0f, 0.0f, 0.0f,		1, 1, 0,
	0.0f, 0.0f, 500.0f,		1, 1, 0,
	0.0f, 0.05f, 0.0f,		1, 1, 0
};

unsigned int indices[] =
{
	0, 1, 2,
	3, 4, 5,
	6, 7, 8
};
Coordinate_Axis::Coordinate_Axis() //:shader(	Shader("Libraries//include//Tool//Shader//coordinate.vert",
					//"Libraries//include//Tool//Shader//coordinate.frag"))
{
	shader = new Shader("Libraries//include//Tool//Shader//coordinate.vert",
						"Libraries//include//Tool//Shader//coordinate.frag");
	

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

}

void Coordinate_Axis::Draw()
{
	shader->Activate();
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

void Coordinate_Axis::Delete()
{
	shader->Delete(); delete shader; shader = nullptr;
	glDeleteVertexArrays(1, &vao);
}