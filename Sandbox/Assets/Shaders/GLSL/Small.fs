#version 420 

out vec4 oColor;
flat in vec3 oNormal;
in vec2 oTexcoord;

uniform sampler2D uTexture;

void main()
{
	vec3 lightDir = normalize(vec3(0.5, 0, -0.25));
	
	float d = clamp(dot(oNormal, -lightDir), 0.0, 1.0);	
	
	oColor = vec4(texture(uTexture, oTexcoord).bgr, 1.0f);	
	oColor += d * 0.25;
}