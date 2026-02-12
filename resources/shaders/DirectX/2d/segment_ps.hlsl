#include <common.hlsli>
#include <2d.hlsli>

#include "body_vs.hlsl"

cbuffer pixelConstants: register(b1) {
    float4 color = float4(1, 1, 0, 0.25f);
}

float4 pixelMain(Pixel2D input): SV_Target {
    return float4(color.rgb, 1);
}
