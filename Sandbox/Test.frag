#version 330 core

out vec4 Color;
in vec3 pos;

void main()
{
	vec3 lightDir = normalize(vec3(0.25, -1, 0.25));

	float d = clamp(dot(-lightDir, pos), 0.0, 1.0);
	
	Color = vec4(vec3(d),1);
}