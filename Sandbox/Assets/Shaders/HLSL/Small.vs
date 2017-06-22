cbuffer DynamicBuffer : register(b1)
{
	float4x4 uVMatrix;
	float4x4 uPMatrix;
	float uTimeSinceStart;
	float3 uCameraPosition;
};

struct VertexInput
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float3 Tangent : TANGENT;
	float3 Bitangent : BITANGENT;
	row_major float4x4 WMatrix : WMATRIX;
};

struct PixelInputType
{
	float4 Position : SV_POSITION;
	nointerpolation float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float3 FragPos : TEXCOORD2;
};

// Vertex Shader
PixelInputType VS_Main(VertexInput input) 
{
	PixelInputType output = (PixelInputType)0;
	
	// Calculate the Position of the vertex against the world, view, and projection matrices.
    output.Position = float4(input.Position, 1.0);
	output.Position = mul(output.Position, input.WMatrix);	
    output.Position = mul(output.Position, uVMatrix);
	output.Position = mul(output.Position, uPMatrix);

	output.Texcoord = input.Texcoord;
		
	//FragPos for calculating specular
	output.FragPos = input.Position;
	
	output.Normal = input.Normal;
	
	return output; 
}