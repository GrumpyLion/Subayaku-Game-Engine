#version 330 core

out vec4 Color;
in vec2 tex;

uniform sampler2D Texture;

void main()
{
	Color = vec4(texture(Texture, tex).xyz, 1.0f);
	//Color = vec4(0,0,0,1);
}