#include <common.hlsli>
#include <2d.hlsli>

cbuffer pixelConstants: register(b1) {
    float alpha = 1.0f;
}

SamplerState pointSampler: register(s0);
Texture2D colorTexture: register(t0);

float4 pixelMain(Pixel2D input): SV_Target {
    float4 color = colorTexture.Sample(pointSampler, input.texCoord);
    return float4(color.rgb, color.a * alpha);
}
