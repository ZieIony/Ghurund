#include <common.hlsli>

cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
    float3 cameraPosition;
    float4 ambientLight;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
}

SamplerState linearSampler : register(s0);
Texture2D diffuseTexture : register(t0);
Texture2D specularTexture : register(t1);
Texture2D normalTexture : register(t2);

static const float3 lightPos = float3(1200, 100, -1500);
static const float4 lightColor = float4(1, 1, 1, 1);

struct Pixel {
    float4 screenPosition: SV_POSITION;
    float3 position : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord: TEXCOORD1;
};

Pixel vertexMain(DefaultVertex input) {
    Pixel output;

    float4 pos = mul(float4(input.position, 1), world);
    output.screenPosition = mul(pos, viewProjection);
    output.position = pos.xyz;
    output.normal = normalize(mul(input.normal, world)).xyz;
    output.tangent = normalize(mul(input.tangent, world)).xyz;
    output.texCoord = input.texCoord;
	
    return output;
}

float4 pixelMain(Pixel input): SV_Target{
	float3x3 toWorld = float3x3(input.tangent, cross(input.tangent, input.normal), input.normal);
	float3 normalMap = normalTexture.Sample(linearSampler, input.texCoord).rgb * 2.0 - 1.0;
	normalMap = mul(normalMap.rgb, toWorld);
	
    float3 normal = normalize(normalMap);
    float3 lightDir = normalize(lightPos - input.position);

    float diffuseIntensity = getDiffuseIntensity(normal, lightDir);
    float4 diffuseColor = diffuseTexture.Sample(linearSampler, input.texCoord);
    float specularIntensity = getSpecularIntensity(input.position, normal, cameraPosition, lightDir, 8);
    float4 specularColor = specularTexture.Sample(linearSampler, input.texCoord);

    return lightColor * (diffuseColor * (ambientLight + diffuseIntensity) + specularColor * specularIntensity);
}
