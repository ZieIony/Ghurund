#include <common.hlsli>

cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
}

SamplerState linearSampler : register(s0);
Texture2D diffuseTexture : register(t0);

DefaultPixel vertexMain(DefaultVertex input) {
    DefaultPixel output;

    output.position = mul(mul(float4(input.position, 1), world), viewProjection);
    output.normal = normalize(mul(input.normal, world)).xyz;
    output.tangent = normalize(mul(input.tangent, world)).xyz;
    output.texCoord = input.texCoord;

    return output;
}

float4 pixelMain(DefaultPixel input): SV_Target{
    float3 lightDir = float3(0, 0, -1);
    float4 lightColor = float4(1, 1, 1, 1);

    float lightIntensity = getDiffuseIntensity(input.normal, lightDir);

    float4 color = diffuseTexture.Sample(linearSampler, input.texCoord);
    return color * lightColor * lightIntensity;
}
