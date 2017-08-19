Texture2D uColor : register(t0);
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
};

// Pixel Shader
float4 PS_Main(PixelInputType input) : SV_TARGET
{	
	float4 Albedo = uColor.Sample(Sampler, input.Texcoord);
	
	float3 lightDir = float3(1,1,1);
	
	float4 ambient = 0.3 * float4(1,1,1,1);
	float d = clamp(dot(input.Normal, lightDir), 0.0, 1.0);
	float4 diffuse = d * float4(1,1,1,1);
	
	return float4((ambient + diffuse) * Albedo);
	//return float4(input.Texcoord, 0, 1);
}