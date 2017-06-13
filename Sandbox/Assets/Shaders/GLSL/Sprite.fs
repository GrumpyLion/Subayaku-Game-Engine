#version 330 core

out vec4 oColor;
in vec2 oTexcoord;

uniform sampler2D uTexture;

void main()
{
	oColor = vec4(texture(uTexture, oTexcoord).xyz, 1.0f);
}