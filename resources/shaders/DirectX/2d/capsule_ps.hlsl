#include <common.hlsli>
#include <sdf.hlsli>
#include <2d.hlsli>

#include "body_vs.hlsl"

cbuffer pixelConstants: register(b1) {
    float4 color = float4(1, 1, 0, 0.25f);
    float2 extents;
}

float4 pixelMain(Pixel2D input): SV_Target {
    float dist = sdCapsule(input.texCoord * extents * 2, extents, extents.x);
    return float4(color.rgb, (step(-2, dist) * 0.75 + 0.25) * step(dist, 0));
}
