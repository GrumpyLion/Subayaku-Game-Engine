#version 420

out vec4 Color;

in vec3 oNormal;
in vec3 oFragPos;
in vec2 oTexCoord;
in vec2 oTexCoordClouds;
in mat3 oTBN;
  
uniform sampler2D uDay;
uniform sampler2D uNight;
uniform sampler2D uClouds;
uniform sampler2D uSpecular;
uniform sampler2D uNormal;

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

	vec3 texNormal = texture(uNormal, oTexCoord).rgb * 2 - 1;
	//the land should pop out!
	texNormal *= vec3(1,1,-1);
	
	vec3 normal = normalize(texNormal * transpose(oTBN));
	
	float d = clamp(dot(normal, -lightDir), 0.0, 1.0);
	
	vec3 viewDir = normalize(uCameraPos.xyz - oFragPos);
	vec3 reflectDir = normalize(reflect(lightDir, normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	spec *= texture(uSpecular, oTexCoord).x;
	
	Color = texture(uNight, oTexCoord);
	Color = mix(Color, texture(uDay, oTexCoord), clamp(d * 1.5f, 0.0, 1.0));
	Color += texture(uClouds, oTexCoordClouds) * 0.5f;
	Color += spec;
	//Color = vec4(vec3(d), 1.0);
}