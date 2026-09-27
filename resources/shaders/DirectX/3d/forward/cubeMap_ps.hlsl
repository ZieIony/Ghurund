#include <common.hlsli>
#include <2d.hlsli>

cbuffer pixelConstants: register(b1) {
    matrix gh_view;
    int2 gh_viewportSize;
}

TextureCube cubeMap: register(t0);
SamplerState linearSampler: register(s0);

float4 pixelMain(DefaultPixel2D input): SV_Target {
    float2 p = (-1.0f + 2.0 * input.texCoord) * gh_viewportSize / gh_viewportSize.y;
    float3 rayDirection = mul((float3x3)gh_view, normalize(float3(p, 1)));

    float4 color = cubeMap.Sample(linearSampler, rayDirection);
    return color;
}
