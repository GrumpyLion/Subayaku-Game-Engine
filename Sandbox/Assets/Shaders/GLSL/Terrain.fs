#version 420

out vec4 Color;

in flat vec3 oNormal;
in vec3 oFragPos;
in vec2 oTexCoord;

in flat vec3 oColor;

uniform sampler2D uColor;

layout (std140, binding = 1) uniform GlobalDynamicBuffer
{ 
  mat4 uPMatrix;
  mat4 uVMatrix;
  vec4 uCameraPos;
  vec2 uTime;
};

void main()
{
	vec3 lightDir = normalize(vec3(0.5, 0, -0.25));
	
	float d = clamp(dot(oNormal, -lightDir), 0.0, 1.0);
	
	vec3 viewDir = normalize(uCameraPos.xyz - oFragPos);
	vec3 reflectDir = normalize(reflect(lightDir, oNormal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
	
	float test = dot(oNormal, viewDir);
	
	vec3 center = vec3(0, 0, 0);
	float dist = distance(center, oFragPos) - 75;
	
	Color = vec4(oColor, 1.0);
	Color += d * 0.25;
	//Color += spec * 0.4;
	Color = mix(Color, vec4(1,1,1,1), clamp(dist * 0.5f, 0.0, 1.0));
	//Color = vec4(vec3(spec), 1.0);
}