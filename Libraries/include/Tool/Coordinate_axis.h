#ifndef COORDINATE_AXIS_H
#define COORDINATE_AXIS_H

#include <Graphics/Graphics.h>
#include <vector>

class Coordinate_Axis
{
protected:
	GLuint vao;

	Shader* shader;

public:
	Coordinate_Axis();
	void Draw();
	Shader getShader() { return *shader; }
	void Delete();
};

#endif // !COORDINATE_AXIS_H
