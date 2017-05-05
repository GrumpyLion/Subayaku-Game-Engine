#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;
layout(location=3) in vec3 tangent;
layout(location=4) in vec3 bitangent;

out vec3 oNormal;
out vec3 oFragPos;
out vec2 oTexCoord;
out vec2 oTexCoordClouds;
out mat3 oTBN;

uniform mat4 uMLMatrix = mat4(1.0);
uniform mat4 uPRMatrix = mat4(1.0);
uniform mat4 uVWMatrix = mat4(1.0);
uniform float uTime;
uniform sampler2D uNormal;
uniform sampler2D uHeight;


void main()
{
	vec4 Pos = uMLMatrix * vec4(position + normal * texture(uHeight, texcoord * vec2(-1, -1)).x * 15, 1.0);
	oFragPos = Pos.xyz;
	
	gl_Position = uPRMatrix * uVWMatrix * Pos;
	
	oNormal = normal;
	
	oTexCoord = texcoord * vec2(-1, -1);
	vec3 texNormal = texture(uNormal, oTexCoord).rgb * 2 - 1;
	
	mat3 TBN;
	TBN[0] = vec4(normalize(uMLMatrix * vec4(tangent, 0.0))).xyz;
	TBN[1] = vec4(normalize(uMLMatrix * vec4(bitangent, 0.0))).xyz;
	TBN[2] = vec4(normalize(uMLMatrix * vec4(oNormal, 0.0))).xyz;
	oTBN = TBN;
	
	oTexCoordClouds = oTexCoord + vec2(uTime*0.000001, 1);
}