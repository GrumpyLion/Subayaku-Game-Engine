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

struct VertexInput
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float3 Tangent : TANGENT;
	float3 Bitangent : BITANGENT;
	float4x4 WMatrix : WMATRIX;
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

float rand(float2 co)
{
    return frac(sin(dot(co.xy ,float2(12.9898,78.233))) * 43758.5453);
}

// Vertex Shader
PixelInputType VS_Main(VertexInput input) 
{
	PixelInputType output = (PixelInputType)0;
	
	// Calculate the Position of the vertex against the world, view, and projection matrices.
    output.Position = float4(input.Position, 1.0);
	
	output.Texcoord = input.Texcoord - float2(0, 1);
	output.DistancePos = input.Position;
	
    output.Position = mul(output.Position, input.WMatrix);
	output.Position.y += uNoise.SampleLevel(Sampler, output.Texcoord, 0) * 50 - 25; 
		
	output.Color = float3(151.0/255.0, 201.0/255.0, 31.0/255);
	output.Color = lerp(output.Color, float3(1, 225.0/255.0, 30.0/255).xyz, clamp(1-output.Position.y * 0.1f, 0.0, 1.0f));
	output.Color *= rand(float2(input.Position.x, input.Position.z)) * 0.25 + 0.7;
	
	//FragPos for calculating specular
	output.FragPos = output.Position;
	
    output.Position = mul(output.Position, uVMatrix);
	output.Position = mul(output.Position, uPMatrix);
	
	//Just copy the normals the interpolation is in the pixel shader
	
	float3 normal = float3(0.0, 0.0, 0.0);
	
	float heightL = uNoise.SampleLevel(Sampler, float2(output.Texcoord.x-1, output.Texcoord.y), 0).y;
	float heightR = uNoise.SampleLevel(Sampler, float2(output.Texcoord.x+1, output.Texcoord.y), 0).y;
	float heightD = uNoise.SampleLevel(Sampler, float2(output.Texcoord.x, output.Texcoord.y-1), 0).y;
	float heightU = uNoise.SampleLevel(Sampler, float2(output.Texcoord.x, output.Texcoord.y+1), 0).y;
	
	normal = float3(heightL - heightR, 2, heightD - heightU);
	normal = normalize(normal);
	
	output.Normal = normal;
	
	return output; 
}