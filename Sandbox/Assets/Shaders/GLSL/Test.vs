#version 420 

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;
layout(location=3) in vec3 Tangent;
layout(location=4) in vec3 Bitangent;

out vec3 oNormal;
out vec3 oFragPos;
out vec2 oTexCoord;
out vec2 oTexCoordClouds;
out mat3 oTBN;

layout (std140, binding = 1) uniform GlobalDynamicBuffer
{ 
  mat4 uPMatrix;
  mat4 uVMatrix;
  vec4 uCameraPos;
  vec2 uTime;
};

uniform mat4 uWMatrix = mat4(1.0);
uniform sampler2D uNormal;
uniform sampler2D uHeight;


void main()
{
	vec4 Pos = uWMatrix * vec4(Position, 1.0); //* vec4(position + normal * texture(uHeight, texcoord * vec2(-1, -1)).x * 15, 1.0);
	oFragPos = Pos.xyz;
	
	gl_Position = uPMatrix * uVMatrix * Pos;
	
	oTexCoord = Texcoord * vec2(-1, -1);
	vec3 texNormal = texture(uNormal, oTexCoord).rgb * 2 - 1;
	
	mat3 TBN;
	TBN[0] = vec4(normalize(uWMatrix * vec4(Tangent, 0.0))).xyz;
	TBN[1] = vec4(normalize(uWMatrix * vec4(Bitangent, 0.0))).xyz;
	TBN[2] = vec4(normalize(uWMatrix * vec4(Normal, 0.0))).xyz;
	oTBN = TBN;

	oNormal = Normal;
	
	oTexCoordClouds = oTexCoord + vec2(uTime.x*0.00001, 1);
}