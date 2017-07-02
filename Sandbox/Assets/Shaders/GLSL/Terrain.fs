#version 420

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec4 gSpecular;
layout (location = 4) out vec4 gFragPosLightSpace;

in flat vec3 oNormal;
in vec3 oFragPos;
in vec4 oFragPosLightSpace;
in vec3 oDistancePos;
in vec2 oTexCoord;

in flat vec3 oColor;

uniform sampler2D uColor;

layout (std140, binding = 1) uniform GlobalDynamicBuffer
{ 
  mat4 uPMatrix;
  mat4 uVMatrix;
  vec4 uCameraPos;
  vec2 uTime;
  
  //Directional Light
  vec4 uLightDirection;
  vec4 uLightColor;
  
  //Shadow mapping
  mat4 uLightSpaceMatrix;
};

void main()
{		
	vec3 center = vec3(0, 0, 0);
	float dist = distance(center, oDistancePos) - 75;
	
	gPosition = vec4(oFragPos, 1.0);
	gNormal = vec4(oNormal, 1.0);
	
	gAlbedo = vec4(oColor, 1.0);
	gAlbedo = mix(gAlbedo, vec4(1,1,1,1), clamp(dist * 0.5f, 0.0, 1.0));
	gSpecular = vec4(0.0, 0.0, 0.0, 1.0);
	gFragPosLightSpace = oFragPosLightSpace;
}