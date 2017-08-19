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
	float3 DistancePos : TEXCOORD4;
};

// Pixel Shader
float4 PS_Main(PixelInputType input):SV_TARGET
{	
	//MOVE THIS TO APPLICATION
	float3 lightDir = normalize(float3(0, -1, 0));
	float d = clamp(dot(input.Normal, -lightDir), 0.0, 1.0); 
	
	float3 viewDir = normalize(uCameraPosition - input.FragPos);
	float3 reflectDir = normalize(reflect(lightDir, input.Normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
	
	float3 center = float3(0, 0, 0);
	float dist = distance(center, input.DistancePos) - 75;
	
	float3 finalColor = input.Color;
	
	finalColor += d * 0.15;
	finalColor += spec * 0.5f;
	
	finalColor = lerp(finalColor, float4(1,1,1,1), clamp(dist * 0.5f, 0.0, 1.0));
	
	return float4(finalColor, 1);
}