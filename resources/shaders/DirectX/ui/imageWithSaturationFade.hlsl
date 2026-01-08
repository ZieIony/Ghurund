#include <common.hlsli>
#include <ui.hlsli>
#include <include/colors.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
    float time;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 350);
    float2 size = float2(300, 300);
    float alpha = 1.0f;
    float4 tint = float4(1, 1, 1, 1);
}

SamplerState linearSampler: register(s0);
Texture2D image: register(t0);

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 pos = screenToClip(input.position.xy * size + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = input.position.xy;

    return output;
}

float getInterpolatedValue(float t) {
    return cos((t + 1) * PI) / 2.0f + 0.5f;
}

float4 pixelMain(UIPixel input): SV_Target {
    float4 color = image.Sample(linearSampler, input.texCoord) * tint;
    float fraction = abs(2 * frac(time / 5) - 1);
    float saturation = getInterpolatedValue(fraction);
    matrix s = makeSaturationMatrix(saturation);
    float brightness = 2 - getInterpolatedValue(min(fraction * 4 / 3, 1));
    float alpha2 = getInterpolatedValue(min(fraction * 2, 1));
    color = saturate(mul(color, brightness));
    color = saturate(mul(color, s));
    return float4(color.rgb, color.a * alpha * alpha2);
}
