#version 420 

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out float gSpecular;
layout (location = 4) out vec4 gFragPosLightSpace;

flat in vec3 oNormal;
in vec3 oFragPos;
in vec4 oFragPosLightSpace;
in vec2 oTexcoord;

uniform sampler2D uTexture;

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
	gPosition = oFragPos;
	gNormal = oNormal;	
	gAlbedo = vec4(texture(uTexture, oTexcoord).rgb, 1.0f);
	gSpecular = 0.0f;
	gFragPosLightSpace = oFragPosLightSpace;
}