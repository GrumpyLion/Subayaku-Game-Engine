#version 330 core

out vec4 Color;
in vec3 pos;

void main()
{
	Color = vec4(pos,1);
}