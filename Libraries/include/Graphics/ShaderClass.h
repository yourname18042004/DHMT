#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		GLuint ID;
		Shader() {}
		Shader(const char* vertexFile, const char* fragmentFile);

		GLuint get_ID() { return ID; }

		void operator = (const Shader& shader);

		void Activate();
		void Delete();
	private:
		void compileErrors(unsigned int shader, const char* type);
};

#endif 

