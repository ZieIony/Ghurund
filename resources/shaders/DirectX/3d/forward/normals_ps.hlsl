#include <common.hlsli>
#include <3d.hlsli>

SamplerState linearSampler: register(s0);
Texture2D normalTexture: register(t3);

float4 pixelMain(DefaultPixel3D input): SV_Target {
    float3x3 toWorld = float3x3(input.tangent, cross(input.tangent, input.normal), input.normal);
    float3 normalMap = normalTexture.Sample(linearSampler, input.texCoord).rgb * 2.0 - 1.0;
    normalMap = mul(normalMap.rgb, toWorld);
    float3 normal = normalize(normalMap);
    float4 color = float4((normal + 1) / 2, 1);
    return color;
}
