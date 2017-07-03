#version 420 

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;
layout(location=3) in vec3 Tangent;
layout(location=4) in vec3 Bitangent;
layout(location=5) in mat4 WMatrix;

out flat vec3 oNormal;
out vec3 oFragPos;
out vec4 oFragPosLightSpace;
out vec2 oTexcoord;

uniform mat4 uWMatrix = mat4(1.0);

// BUFFERS ------------------------------

layout (std140, binding = 1) uniform GlobalDynamicBuffer
{ 
	mat4 uPMatrix;
	mat4 uVMatrix;
	vec4 uCameraPos;
	vec2 uTime;

	//Directional Light
	vec4 uLightDirection;
	vec4 uLightColor;
};

layout (std140, binding = 2) uniform ShadowBuffer
{
	mat4 uLightSpaceMatrix;
};

// BUFFERS ------------------------------

void main()
{	
	vec4 Pos = WMatrix * vec4(Position, 1.0);
	
	oFragPos = Pos.xyz;
	oFragPosLightSpace = uLightSpaceMatrix * vec4(oFragPos, 1.0);
	
	gl_Position = uPMatrix * uVMatrix * Pos;
	
	oNormal = Normal;
	oTexcoord = Texcoord - vec2(0, 1);
}