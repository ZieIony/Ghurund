#include <common.hlsli>
#include <ui.hlsli>
#include <colors.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 350);
    float2 size = float2(300, 300);
    float4 tint = float4(1, 1, 1, 1);
    float focused = 0.0f;
    float enabled = 0.0f;
    float checked = 0.0f;
    float alpha = 1.0f;
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

float4 pixelMain(UIPixel input): SV_Target {
    float2 texCoord = input.texCoord * float2(0.5f, 1) + checked * float2(0.5f, 0);
    float4 color = image.Sample(linearSampler, texCoord) * tint;
    color = saturate(mul(color, makeBrightnessMatrix(1 + focused / 2)));
    color = saturate(mul(color, makeSaturationMatrix(enabled / 2 + 0.5)));
    return float4(color.rgb, color.a * alpha);
}
