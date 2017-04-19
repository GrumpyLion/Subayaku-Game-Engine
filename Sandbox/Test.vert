#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

out vec3 pos;

uniform mat4 uMLMatrix;
uniform mat4 uPRMatrix;

void main()
{
	gl_Position = uPRMatrix * uMLMatrix * vec4(position, 1.0);
	pos = mat3(transpose(inverse(uMLMatrix))) * normal;
}