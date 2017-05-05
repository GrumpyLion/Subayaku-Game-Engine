Texture2D shaderTexture;
SamplerState SampleType;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
};

// Pixel Shader
float4 PS_Main(PixelInputType input):SV_TARGET
{
    return float4(input.normal,1);
}