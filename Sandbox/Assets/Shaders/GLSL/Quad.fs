#version 420 

out vec4 oColor;
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
	oColor = vec4(texture(uTexture, oTexcoord).xyz,1.0);	
}