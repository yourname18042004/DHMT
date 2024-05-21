#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 View;

out vec3 color;

void main()
{
	vec4 pass = vec4(aPos, 1.0);

	gl_Position = View * pass ;
	
	color = aColor;
}