#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 passColor;

uniform mat4 View;

void main()
{
	vec4 tmp = View * vec4(aPos, 1.0);
	gl_Position = vec4(tmp.x, tmp.y, 0, tmp.z);
	passColor = aColor;
}