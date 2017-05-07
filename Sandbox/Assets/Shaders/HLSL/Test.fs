Texture2D uDay : register(t0);
Texture2D uNight : register(t1);
Texture2D uNormal : register(t2);
Texture2D uSpecular : register(t3);
Texture2D uClouds : register(t4);

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
	float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD;
	float2 TexcoordClouds : TEXCOORD1;
	float3 FragPos : TEXCOORD2;
	float3x3 TBN : TEXCOORD3;
};

// Pixel Shader
float4 PS_Main(PixelInputType input):SV_TARGET
{
	//Get the normal data
	float3 texNormal = normalize(uNormal.Sample(Sampler, input.Texcoord).rgb * 2 - 1);
	texNormal *= float3(1,1,-1);
	
	float3 normal = normalize(mul(texNormal, input.TBN));	
	
	//MOVE THIS TO APPLICATION
	float3 lightDir = normalize(float3(0.5, 0, -0.25));
	float d = clamp(dot(normal, -lightDir), 0.0, 1.0); 

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
	float3 dayColor = uDay.Sample(Sampler, input.Texcoord).rgb;
	float3 nightColor = uNight.Sample(Sampler, input.Texcoord).rgb;
    float4 cloudsColor = uClouds.Sample(Sampler, input.TexcoordClouds);
	
	float3 viewDir = normalize(uCameraPosition - input.FragPos);
	float3 reflectDir = normalize(reflect(lightDir, normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	spec *= uSpecular.Sample(Sampler, input.Texcoord).r;
	
	float4 finalColor = float4(lerp(nightColor, dayColor, clamp(d * 1.5f, 0.0, 1.0)), 1.0);
	finalColor += cloudsColor * 0.5f;
	finalColor += spec;
	
	return finalColor;
}