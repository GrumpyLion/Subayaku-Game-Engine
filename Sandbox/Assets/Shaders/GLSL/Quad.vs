#version 420 

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;
layout(location=3) in vec3 Tangent;
layout(location=4) in vec3 Bitangent;
layout(location=5) in mat4 WMatrix;

out vec2 oTexcoord;

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
	gl_Position = vec4(Position, 1.0);
	oTexcoord = Texcoord;
}