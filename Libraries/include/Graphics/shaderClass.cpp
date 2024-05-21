#include "ShaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) 
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// tao mot doi tuong vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// gan vertex Shader Source vao doi tuong vertex shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// bien dich thanh ma may
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// tuong tu nhu vertex Shader
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// tao doi tuong shader program 
	ID = glCreateProgram();
	// gan vertex va fragment shader vao shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// lien ket tat cac cac shader lai voi nhau de tao thanh ShaderProgam
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// xoa vertexShader va fragmentShader vi khong con can thiet
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// chua dung trang thai bien dich
	GLint hasCompiled;
	// chuoi ky tu in ra loi cua shader
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

void Shader::operator = (const Shader& shader)
{
	ID = shader.ID;
}