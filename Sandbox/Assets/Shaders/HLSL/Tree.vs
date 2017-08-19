Texture2D uColor : register(t0);
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
	row_major float4x4 WMatrix : WMATRIX;
};

struct PixelInputType
{
	float4 Position : SV_POSITION;
	nointerpolation float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float3 FragPos : TEXCOORD2;
};

//https://thebookofshaders.com/11/
// Some useful functions
float3 mod289(float3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
float2 mod289(float2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
float3 permute(float3 x) { return mod289(((x*34.0)+1.0)*x); }

float snoise(float2 v) {

    // Precompute values for skewed triangular grid
    const float4 C = float4(0.211324865405187,
                        // (3.0-sqrt(3.0))/6.0
                        0.366025403784439,  
                        // 0.5*(sqrt(3.0)-1.0)
                        -0.577350269189626,  
                        // -1.0 + 2.0 * C.x
                        0.024390243902439); 
                        // 1.0 / 41.0

    // First corner (x0)
    float2 i  = floor(v + dot(v, C.yy));
    float2 x0 = v - i + dot(i, C.xx);

    // Other two corners (x1, x2)
    float2 i1 = float2(0.0, 0.0);
    i1 = (x0.x > x0.y)? float2(1.0, 0.0):float2(0.0, 1.0);
    float2 x1 = x0.xy + C.xx - i1;
    float2 x2 = x0.xy + C.zz;

    // Do some permutations to avoid
    // truncation effects in permutation
    i = mod289(i);
    float3 p = permute(
            permute( i.y + float3(0.0, i1.y, 1.0))
                + i.x + float3(0.0, i1.x, 1.0 ));

    float3 m = max(0.5 - float3(
                        dot(x0,x0), 
                        dot(x1,x1), 
                        dot(x2,x2)
                        ), 0.0);

    m = m*m ;
    m = m*m ;

    // Gradients: 
    //  41 pts uniformly over a line, mapped onto a diamond
    //  The ring size 17*17 = 289 is close to a multiple 
    //      of 41 (41*7 = 287)

    float3 x = 2.0 * frac(p * C.www) - 1.0;
    float3 h = abs(x) - 0.5;
    float3 ox = floor(x + 0.5);
    float3 a0 = x - ox;

    // Normalise gradients implicitly by scaling m
    // Approximation of: m *= inversesqrt(a0*a0 + h*h);
    m *= 1.79284291400159 - 0.85373472095314 * (a0*a0+h*h);

    // Compute final noise value at P
    float3 g = float3(0.0, 0.0, 0.0);
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * float2(x1.x,x2.x) + h.yz * float2(x1.y,x2.y);
    return 130.0 * dot(m, g);
}

// Vertex Shader
PixelInputType VS_Main(VertexInput input) 
{
	PixelInputType output = (PixelInputType)0;		
		
	output.Texcoord = input.Texcoord - float2(0, 1);
		
	// Calculate the Position of the vertex against the world, view, and projection matrices.
    output.Position = float4(input.Position, 1.0);
	output.Position = mul(output.Position, input.WMatrix);	
	
	float2 waveCoords = output.Position.xz * float2(3.5, 3.5) + float2(uTimeSinceStart, uTimeSinceStart) * float2(0.00025, 0.00025);
	
	if(uColor.SampleLevel(Sampler, output.Texcoord, 0).x < 0.5f)
	{
		output.Position.y += snoise(waveCoords);
		output.Position.xz += float2((snoise(waveCoords)-0.5f) * 2.0f, (snoise(-waveCoords)-0.5f)  * 2.0f);
	}
		
    output.Position = mul(output.Position, uVMatrix);
	output.Position = mul(output.Position, uPMatrix);
		
	//FragPos for calculating specular
	output.FragPos = input.Position;
	
	output.Normal = input.Normal;
	
	return output; 
}