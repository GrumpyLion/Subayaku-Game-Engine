#version 420 

out vec4 oColor;
in vec2 oTexcoord;

uniform sampler2D uAlbedo;
uniform sampler2D uNormal;
uniform sampler2D uPosition;
uniform sampler2D uVignette;

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

void main()
{	
	vec3 FragPos = texture(uPosition, oTexcoord).rgb;
	vec3 Normal = texture(uNormal, oTexcoord).rgb;
	vec4 Albedo = texture(uAlbedo, oTexcoord);
	
	vec4 ambient = 0.1 * uLightColor;
	float d = clamp(dot(Normal, uLightDirection.xyz), 0.0, 1.0);
	vec4 diffuse = d * uLightColor;
	
	vec3 viewDir = normalize(uCameraPos.xyz - FragPos);
	vec3 reflectDir = normalize(reflect(uLightDirection.xyz, Normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
	
	oColor = (ambient + diffuse) * Albedo;
	oColor += spec * 0.;
	oColor -= vec4(vec3(texture(uVignette, oTexcoord).a * 0.5), 1.0);
	oColor = vec4(oColor.xyz, 1.0);
}