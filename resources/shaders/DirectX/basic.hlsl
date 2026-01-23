#include <common.hlsli>

cbuffer perCamera: register(b0) {
    row_major float4x4 viewProjection;
}

cbuffer perObject: register(b1) {
    row_major float4x4 world;
}

SamplerState linearSampler: register(s0);
Texture2D diffuseTexture: register(t0);

struct DefaultVertex2 {
    float3 position: POSITION;
    float3 normal: NORMAL;
    float2 texCoord: TEXCOORD0;
};

struct DefaultPixel2 {
    float4 position: SV_POSITION;
    float3 normal: NORMAL;
    float2 texCoord: TEXCOORD0;
};

DefaultPixel2 vertexMain(DefaultVertex2 input) {
    DefaultPixel2 output;

    output.position = mul(mul(float4(input.position, 1), world), viewProjection);
    output.normal = normalize(mul(input.normal, world)).xyz;
    //output.tangent = normalize(mul(input.tangent, world)).xyz;
    output.texCoord = input.texCoord;

    return output;
}

float4 pixelMain(DefaultPixel2 input): SV_Target {
    //float4 color = diffuseTexture.Sample(linearSampler, frac(input.texCoord*5));
    float4 color = float4(1, 1, 1, 1);
    return color;
}
