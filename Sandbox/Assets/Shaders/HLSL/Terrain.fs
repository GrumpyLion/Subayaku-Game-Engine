Texture2D uNoise : register(t0);
Texture2D uColor : register(t1);

SamplerState Sampler;

cbuffer DynamicBuffer : register(b1)
{
	float4x4 uVMatrix;
	float4x4 uPMatrix;
	float uTimeSinceStart;
	float3 uCameraPosition;
};

struct PixelInputType
{
	float4 Position : SV_POSITION;
	nointerpolation float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float3 FragPos : TEXCOORD2;
	
	nointerpolation  float3 Color : TEXCOORD3;
};

// Pixel Shader
float4 PS_Main(PixelInputType input):SV_TARGET
{	
	//MOVE THIS TO APPLICATION
	float3 lightDir = normalize(float3(0.5, 0, -0.25));
	float d = clamp(dot(input.Normal, -lightDir), 0.0, 1.0); 
	
	float3 viewDir = normalize(uCameraPosition - input.FragPos);
	float3 reflectDir = normalize(reflect(lightDir, input.Normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	
	float3 center = float3(0, 0, 0);
	float dist = distance(center, input.FragPos) - 45;
	
	float3 finalColor = input.Color;
	
	finalColor += d * 0.25;
	finalColor += spec * 0.4;
	
	finalColor = lerp(finalColor, float4(1,1,1,1), clamp(dist * 0.5f, 0.0, 1.0));
	
	return float4(finalColor, 1);
}