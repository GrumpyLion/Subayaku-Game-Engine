cbuffer DynamicBuffer : register(b1)
{
	float4x4 uVMatrix;
	float4x4 uPMatrix;
	float uTimeSinceStart;
	float3 uCameraPosition;
};

cbuffer ObjectBuffer : register(b5)
{
	float4x4 uWMatrix;
};

struct VertexInput
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float3 Tangent : TANGENT;
	float3 Bitangent : BITANGENT;
};

struct PixelInputType
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float2 TexcoordClouds : TEXCOORD1;
	float3 FragPos : TEXCOORD2;
	float3x3 TBN : TEXCOORD3;
};

// Vertex Shader
PixelInputType VS_Main(VertexInput input) 
{
	PixelInputType output = (PixelInputType)0;
	
	// Calculate the Position of the vertex against the world, view, and projection matrices.
    output.Position = float4(input.Position, 1.0);
    output.Position = mul(output.Position, uWMatrix);
    output.Position = mul(output.Position, uVMatrix);
	output.Position = mul(output.Position, uPMatrix);
	
	output.Texcoord = input.Texcoord;
	output.Texcoord *= float2(-1.0,-1.0);
	output.TexcoordClouds = output.Texcoord + float2(uTimeSinceStart * 0.00001, 0.0);
	
	//FragPos for calculating specular
	output.FragPos = mul(input.Position, (float3x3)uWMatrix);
	
	//TBN Matrix for Normal mapping
	float3x3 TBN;
	TBN[0] = normalize(mul(input.Tangent, (float3x3)uWMatrix));
	TBN[1] = normalize(mul(input.Bitangent, (float3x3)uWMatrix));
	TBN[2] = normalize(mul(input.Normal, (float3x3)uWMatrix));
	output.TBN = TBN;
	
	//Just copy the normals the interpolation is in the pixel shader
	output.Normal = input.Normal;
	
	return output; 
}