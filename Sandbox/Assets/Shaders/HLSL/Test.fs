Texture2D uDay : register(t0);
Texture2D uNight : register(t1);
Texture2D uNormal : register(t2);
Texture2D uSpecular : register(t3);
Texture2D uClouds : register(t4);

SamplerState Sampler;

cbuffer DynamicBuffer : register(b1)
{
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float TimeSinceStart;
	float3 CameraPosition;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float2 texcoordClouds : TEXCOORD1;
	float3 fragPos : TEXCOORD2;
};

// Pixel Shader
float4 PS_Main(PixelInputType input):SV_TARGET
{
	float3 lightDir = normalize(float3(0.5, 0, -0.25));
	float d = clamp(dot(input.normal, -lightDir), 0.0, 1.0); 

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
	float3 dayColor = uDay.Sample(Sampler, input.texcoord).rgb;
	float3 nightColor = uNight.Sample(Sampler, input.texcoord).rgb;
    float4 cloudsColor = uClouds.Sample(Sampler, input.texcoordClouds);
	
	float3 viewDir = normalize(CameraPosition - input.fragPos);
	float3 reflectDir = normalize(reflect(-lightDir, input.normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	spec *= uSpecular.Sample(Sampler, input.texcoord).r;
	
	float4 finalColor = float4(lerp(nightColor, dayColor, d * 1.5f), 1.0);
	finalColor += cloudsColor * 0.5f;
	finalColor += spec;
	
	return finalColor;
}