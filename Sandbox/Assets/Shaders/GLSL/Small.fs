#version 420 

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;

flat in vec3 oNormal;
in vec3 oFragPos;
in vec2 oTexcoord;

uniform sampler2D uTexture;

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

void main()
{	
	gPosition = vec4(oFragPos, 1.0);
	gNormal = vec4(oNormal, 1.0);	
	gAlbedo = vec4(texture(uTexture, oTexcoord).rgb, 1.0f);
}