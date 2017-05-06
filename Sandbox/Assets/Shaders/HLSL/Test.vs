cbuffer DynamicBuffer : register(b1)
{
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float TimeSinceStart;
	float3 CameraPosition;
};

cbuffer ObjectBuffer : register(b5)
{
	float4x4 worldMatrix;
};

struct VertexInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float2 texcoordClouds : TEXCOORD1;
	float3 fragPos : TEXCOORD2;
};

// Vertex Shader
PixelInputType VS_Main(VertexInput input) 
{
	PixelInputType output = (PixelInputType)0;
	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = float4(input.position, 1.0);
    output.position = mul(output.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.normal = normalize(mul(input.normal, (float3x3)worldMatrix));
	
	output.texcoord = input.texcoord;
	output.texcoord *= float2(-1.0,-1.0);
	output.texcoordClouds = output.texcoord + float2(TimeSinceStart * 0.00001, 0.0);
	
	output.fragPos = mul(input.position, (float3x3)worldMatrix);
	
	return output; 
}