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

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(uShadow, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
	
    float bias = max(0.05 * (1.0 - dot(normal, uLightDirection.xyz)), 0.005);
	
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(uShadow, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(uShadow, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{	
	vec3 FragPos = texture(uPosition, oTexcoord).rgb;
	vec3 Normal = texture(uNormal, oTexcoord).rgb;
	vec4 Albedo = texture(uAlbedo, oTexcoord);
	float Specular = texture(uSpecular, oTexcoord).x;
	vec4 FragPosLightSpace = texture(uFragPosLightSpace, oTexcoord);
	
	vec4 ambient = 0.1 * uLightColor;
	float d = clamp(dot(Normal, uLightDirection.xyz), 0.0, 1.0);
	vec4 diffuse = d * uLightColor;
	
	vec3 viewDir = normalize(uCameraPos.xyz - FragPos);
	vec3 reflectDir = normalize(reflect(-uLightDirection.xyz, Normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
	
	float shadow = ShadowCalculation(FragPosLightSpace, Normal); 
	
	oColor = (ambient + (1-shadow) * diffuse) * Albedo;
	oColor += vec4(vec3(spec * Specular), 1.0);
	oColor -= vec4(vec3(texture(uVignette, oTexcoord).a * 0.5), 1.0);
	oColor = vec4(oColor.xyz, 1.0);
	//oColor = vec4(vec3(texture(uShadow, oTexcoord).r), 1.0);
	//oColor += FragPosLightSpace;
}