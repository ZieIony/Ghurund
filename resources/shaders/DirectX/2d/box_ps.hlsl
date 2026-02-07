#include <common.hlsli>
#include <sdf.hlsli>
#include <2d.hlsli>

#include "body_vs.hlsl"

cbuffer pixelConstants: register(b1) {
    float4 color = float4(1, 1, 0, 0.25f);
}

float4 pixelMain(Pixel2D input): SV_Target {
    float dist = sdRect(input.texCoord.xy - float2(0.5, 0.5), float2(0.5, 0.5));
    float4 color2 = float4(1, 1, 1, 0.5f);
    //float pattern = frac(atan2(input.texCoord.y - 0.5, input.texCoord.x - 0.5) * 2);
    return lerp(float4(color.rgb, 0.25), color2, step(-0.01, dist));// * step(0.5, pattern));
}
