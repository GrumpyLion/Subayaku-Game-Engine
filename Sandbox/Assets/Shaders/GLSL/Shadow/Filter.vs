#version 420

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;
layout(location=3) in vec3 Tangent;
layout(location=4) in vec3 Bitangent;
layout(location=5) in mat4 WMatrix;

out vec2 oTexCoord;

void main()
{
	gl_Position = vec4(Position, 1.0);
	oTexCoord = Texcoord;
}