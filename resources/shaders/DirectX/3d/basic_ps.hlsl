#include <common.hlsli>
#include <3d.hlsli>

SamplerState linearSampler: register(s0);
Texture2D diffuseTexture: register(t0);

float4 pixelMain(Pixel3D input): SV_Target {
    //float4 color = diffuseTexture.Sample(linearSampler, frac(input.texCoord*5));
    float4 color = float4(1, 1, 1, 1);
    return color;
}
