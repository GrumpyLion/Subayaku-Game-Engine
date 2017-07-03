#version 420

out vec4 oColor;
in vec2 oTexCoord;

uniform sampler2D uTexture;
uniform vec2 uBlur;

void main()
{
	vec4 color = vec4(0.0);

	color += texture(uTexture, oTexCoord + (vec2(-3.0) * uBlur)) * (1.0/64.0);
	color += texture(uTexture, oTexCoord + (vec2(-2.0) * uBlur)) * (6.0/64.0);
	color += texture(uTexture, oTexCoord + (vec2(-1.0) * uBlur)) * (15.0/64.0);
	color += texture(uTexture, oTexCoord + (vec2(0.0) * uBlur))  * (20.0/64.0);
	color += texture(uTexture, oTexCoord + (vec2(1.0) * uBlur))  * (15.0/64.0);
	color += texture(uTexture, oTexCoord + (vec2(2.0) * uBlur))  * (6.0/64.0);
	color += texture(uTexture, oTexCoord + (vec2(3.0) * uBlur))  * (1.0/64.0);

	oColor = color;
}