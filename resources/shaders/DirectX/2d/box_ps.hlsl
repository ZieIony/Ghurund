#include <common.hlsli>
#include <sdf.hlsli>
#include <2d.hlsli>
#include "2d_vs.hlsl"

cbuffer pixelConstants: register(b1) {
    float4 color = float4(1, 1, 1, 0.5f);
}

float4 pixelMain(Pixel2D input): SV_Target {
    return color;
}
