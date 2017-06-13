#version 330 core

layout(location=0) in vec3 iPosition;
layout(location=2) in vec2 iTexcoord;

out vec2 oTexcoord;

uniform mat4 uMLMatrix;
uniform mat4 uORMatrix;
uniform mat4 uPRMatrix;

void main()
{
	gl_Position = uORMatrix * uMLMatrix * vec4(iPosition, 1.0);
	oTexcoord = iTexcoord;
}