#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec2 texcoord;

out vec2 tex;

uniform mat4 uMLMatrix;
uniform mat4 uPRMatrix;

void main()
{
	gl_Position = vec4(position, 1.0);
	tex = texcoord;
}