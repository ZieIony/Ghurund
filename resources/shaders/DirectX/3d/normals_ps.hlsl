#include <common.hlsli>
#include <3d.hlsli>

SamplerState linearSampler: register(s0);
Texture2D diffuseTexture: register(t0);

float4 pixelMain(Pixel3D input): SV_Target {
    float4 color = float4((input.normal + 1)/2, 1);
    return color;
}
