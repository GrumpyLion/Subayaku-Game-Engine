#version 420 

out vec4 oColor;
in vec2 oTexcoord;

uniform sampler2D uAlbedo;
uniform sampler2D uNormal;
uniform sampler2D uPosition;
uniform sampler2D uSpecular;
uniform sampler2D uFragPosLightSpace;
uniform sampler2D uShadow;
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

float linstep(float low, float high, float v)
{
	return clamp((v-low)/(high-low), 0.0, 1.0);
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
   
   // transform to [0,1] range  
	projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    
	float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
	
	vec2 moments = texture2D(uShadow, projCoords.xy).xy;
	
	float p = step(currentDepth, moments.x);
	float variance = max(moments.y - moments.x * moments.x, 0.00002);
	
	float d = currentDepth - moments.x;
	float pMax = linstep(0.1, 1.0, variance / (variance + d*d));
	
	if(projCoords.z > 1.0) 
		return 1;
	
	return min(max(p, pMax), 1.0);
}

void main()
{	
	vec3 FragPos = texture(uPosition, oTexcoord).rgb;
	vec3 Normal = texture(uNormal, oTexcoord).rgb;
	vec4 Albedo = texture(uAlbedo, oTexcoord);
	float Specular = texture(uSpecular, oTexcoord).x;
	vec4 FragPosLightSpace = texture(uFragPosLightSpace, oTexcoord);
	
	vec4 ambient = 0.3 * uLightColor;
	float d = clamp(dot(Normal, uLightDirection.xyz), 0.0, 1.0);
	vec4 diffuse = d * uLightColor;
	
	vec3 viewDir = normalize(uCameraPos.xyz - FragPos);
	vec3 reflectDir = normalize(reflect(-uLightDirection.xyz, Normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
	
	float shadow = ShadowCalculation(FragPosLightSpace); 
	
	if(length(FragPosLightSpace) == 0.0f) 
		shadow = 1.0f;
		
	oColor = (ambient  + diffuse) * Albedo - (1-clamp(shadow, 0.0, 1.0))*0.35f;
	oColor += vec4(vec3(spec * Specular), 1.0);
	oColor -= vec4(vec3(texture(uVignette, oTexcoord).a * 0.5), 1.0);
	oColor = vec4(oColor.xyz, 1.0);
	//oColor = vec4(texture(uShadow, oTexcoord).xy, 0.0, 1.0);
	//oColor = vec4(Normal, 1.0);
	//oColor = FragPosLightSpace;
}