#version 420 

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;
layout(location=3) in vec3 Tangent;
layout(location=4) in vec3 Bitangent;
layout(location=5) in mat4 WMatrix;

layout (std140, binding = 2) uniform ShadowBuffer
{
	mat4 uLightSpaceMatrix;
};

void main()
{		
	gl_Position = uLightSpaceMatrix * WMatrix * vec4(Position, 1.0);
}