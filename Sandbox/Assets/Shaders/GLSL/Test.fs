#version 330 core

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

uniform vec3 uCameraPos;

void main()
{
	vec3 lightDir = normalize(vec3(0.5, 0, -0.25));

	vec3 texNormal = texture(uNormal, oTexCoord).rgb * 2 - 1;
	//the land should pop out!
	texNormal *= vec3(1,-1,1);
	
	vec3 normal = normalize(texNormal * transpose(oTBN));
	
	float d = clamp(dot(normal, -lightDir), 0.0, 1.0);
	
	vec3 viewDir = normalize(uCameraPos - oFragPos);
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	spec *= texture(uSpecular, oTexCoord).x;
	
	Color = texture(uNight, oTexCoord);
	Color = mix(Color, texture(uDay, oTexCoord), d);
	Color += texture(uClouds, oTexCoordClouds) * 0.5f;
	Color += spec;
	//Color = vec4(vec3(d), 1.0);
}