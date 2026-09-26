#include <common.hlsli>
#include <3d.hlsli>

SamplerState linearSampler: register(s0);
Texture2D diffuseTexture: register(t0);

float4 pixelMain(DefaultPixel3D input): SV_Target {
    float4 color = diffuseTexture.Sample(linearSampler, input.texCoord);
    return color;
}
