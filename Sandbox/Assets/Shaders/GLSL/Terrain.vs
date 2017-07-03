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
out vec2 oTexCoord;
out vec3 oDistancePos;

out flat vec3 oColor;

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

// Textures
uniform sampler2D uNoise;
uniform sampler2D uColor;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec4 Pos = WMatrix * vec4(Position, 1.0);
	
	oTexCoord = Texcoord - vec2(0, 1);
	
	oDistancePos = Position.xyz;
	Pos.y += texture(uNoise, oTexCoord).y * clamp(uTime.x * 0.0005, 0.0, 1.0) * 50 - 25;	
	
	oFragPos = Pos.xyz;
	oFragPosLightSpace = uLightSpaceMatrix * vec4(oFragPos, 1.0);
	
	gl_Position = uPMatrix * uVMatrix * Pos;
		
	float amount = texture(uNoise, oTexCoord).x * 0.5f;
	
	vec3 col = texture(uColor, vec2(4.0 / 5.0, 0)).xyz;
	col = mix(col, texture(uColor, vec2(1, 0)).xyz, clamp(1-Pos.y * 0.1f, 0.0, 1.0)).xyz;
	//col = mix(col, texture(uColor, vec2(3.0 / 5.0, 0)).xyz, amount);
	float r = rand(vec2(Position.x, Position.z)) * 0.25 + 0.7;
	col *= vec3(r, r, r);
	
	oColor = col;
	
	vec3 normal = vec3(0.0);
	
	float heightL = texture(uNoise, vec2(oTexCoord.x-1, oTexCoord.y)).y;
	float heightR = texture(uNoise, vec2(oTexCoord.x+1, oTexCoord.y)).y;
	float heightD = texture(uNoise, vec2(oTexCoord.x , oTexCoord.y-1)).y;
	float heightU = texture(uNoise, vec2(oTexCoord.x , oTexCoord.y+1)).y;
	
	normal = vec3(heightL - heightR, 1, heightD - heightU);
	normal = normalize(normal);
	
	oNormal = normal;
}