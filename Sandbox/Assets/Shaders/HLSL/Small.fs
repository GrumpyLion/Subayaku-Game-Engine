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
	return float4(0,1,0, 1);
}