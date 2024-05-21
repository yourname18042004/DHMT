#ifndef DOC_FILE_CLASS_H
#define DOC_FILE_CLASS_H

#include <Graphics/Display.h>
#include <string>
#include "docFileVRML.h"

class DocFile : public Display
{

private:
	Camera camera;
	
	int size;
	Shader shader;
	Shader box_shader;
	Shader shadow_shader;

	GLuint vao;
	std::string filepath;
public:
	DocFile(std::string filepath, int width, int height);
	void InitObject();
	void Draw();
};

#endif