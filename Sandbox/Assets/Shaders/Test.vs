#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;

out vec3 pos;
out vec2 tex;

uniform mat4 uMLMatrix;
uniform mat4 uPRMatrix;

void main()
{
	gl_Position = uPRMatrix * uMLMatrix * vec4(position, 1.0);
	pos = mat3(transpose(inverse(uMLMatrix))) * normal;
	tex = texcoord;
}