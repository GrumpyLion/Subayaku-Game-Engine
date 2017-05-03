#version 330 core

out vec4 Color;
in vec3 pos;
in vec3 fragPos;
in vec2 tex;
  
uniform sampler2D Texture;

void main()
{
	vec3 lightDir = normalize(vec3(0.25, -1, 0.25));

	float d = clamp(dot(-lightDir, pos), 0.0, 1.0);
	
	Color = vec4(vec3(d),1);
	//Color = texture(Texture, tex);
}