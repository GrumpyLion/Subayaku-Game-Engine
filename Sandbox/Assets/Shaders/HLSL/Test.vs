cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
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
	output.normal = input.normal;
	return output; 
}