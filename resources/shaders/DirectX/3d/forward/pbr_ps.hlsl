#include <common.hlsli>
#include <3d.hlsli>
#include <pbr.hlsli>

cbuffer pixelConstants : register(b0) {
    float3 gh_cameraPosition;
}

SamplerState linearSampler : register(s0);
Texture2D albedoTexture : register(t0);
Texture2D metallicTexture : register(t1);
Texture2D roughnessTexture: register(t2);
Texture2D normalTexture : register(t3);
Texture2D aoTexture: register(t4);

static const float3 lightPos = float3(120, 10, -150);
static const float3 lightColor = float3(1, 1, 1);
static const float3 ambientLightColor = float3(0.2, 0.2, 0.2);

float4 pixelMain(DefaultPixel3D input): SV_Target{
	float3x3 toWorld = float3x3(input.tangent, cross(input.tangent, input.normal), input.normal);
	float3 normalMap = normalTexture.Sample(linearSampler, input.texCoord).rgb * 2.0 - 1.0;
	normalMap = mul(normalMap.rgb, toWorld);
    float3 normal = normalize(normalMap);

    float4 albedoColor = albedoTexture.Sample(linearSampler, input.texCoord);
    float roughness = roughnessTexture.Sample(linearSampler, input.texCoord).r;
    float metallic = metallicTexture.Sample(linearSampler, input.texCoord).r;
    float ao = aoTexture.Sample(linearSampler, input.texCoord).r;

    float3 color = pbr(
        input.position,
        gh_cameraPosition,
        normal,
        albedoColor.rgb,
        metallic,
        roughness,
        lightPos,
        lightColor,
        ambientLightColor,
        ao
    );
    
    return float4(color, 1);
}
