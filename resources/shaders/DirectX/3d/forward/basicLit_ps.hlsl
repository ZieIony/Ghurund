#include <common.hlsli>
#include <3d.hlsli>

cbuffer pixelConstants : register(b0) {
    float3 gh_cameraPosition;
    float4 ambientLight;
}

SamplerState linearSampler : register(s0);
Texture2D diffuseTexture : register(t0);
Texture2D specularTexture : register(t1);
Texture2D normalTexture : register(t2);

static const float3 lightPos = float3(1200, 100, -1500);
static const float4 lightColor = float4(1, 1, 1, 1);

float4 pixelMain(DefaultPixel3D input): SV_Target{
	float3x3 toWorld = float3x3(input.tangent, cross(input.tangent, input.normal), input.normal);
	float3 normalMap = normalTexture.Sample(linearSampler, input.texCoord).rgb * 2.0 - 1.0;
	normalMap = mul(normalMap.rgb, toWorld);
	
    float3 normal = normalize(normalMap);
    float3 lightDir = normalize(lightPos - input.position);

    float diffuseIntensity = getDiffuseIntensity(normal, lightDir);
    float4 diffuseColor = diffuseTexture.Sample(linearSampler, input.texCoord);
    float specularIntensity = getSpecularIntensity(input.position, normal, gh_cameraPosition, lightDir, 8);
    float4 specularColor = specularTexture.Sample(linearSampler, input.texCoord);

    return lightColor * (diffuseColor * (ambientLight + diffuseIntensity) + specularColor * specularIntensity);
}
