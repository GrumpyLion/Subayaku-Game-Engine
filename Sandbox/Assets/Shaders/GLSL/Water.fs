#version 420

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out float gSpecular;
layout (location = 4) out vec4 gFragPosLightSpace;

in flat vec3 oNormal;
in vec3 oFragPos;
in vec4 oFragPosLightSpace;
in vec3 oDistancePos;
in vec2 oTexCoord;

in flat vec3 oColor;

uniform sampler2D uColor;
uniform sampler2D uNoise;

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
	
	vec3 center = vec3(0, 0, 0);
	float dist = distance(center, oDistancePos) - 75;
	
	gAlbedo = vec4(oColor, 1.0);
	gAlbedo = mix(gAlbedo, vec4(1,1,1,1), clamp(dist * 0.5f, 0.0, 1.0));
	gNormal = mix(gNormal, vec3(1,1,1), clamp(dist * 0.5f, 0.0, 1.0));
	
	gSpecular = 0.5f;
	gFragPosLightSpace = oFragPosLightSpace;
}