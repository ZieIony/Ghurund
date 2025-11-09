#include <common.hlsli>
#include <sdf.hlsli>

#define transparencyEnabled

cbuffer perCamera: register(b0) {
    int2 mousePos;
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 50);
    float2 size = float2(120, 40);
    float4 backgroundColor;
    float4 borderColor;
    float4 cornerRadius = float4(4, 4, 4, 4);
    float borderWidth = 1;
}

SamplerState linearSampler: register(s0);
Texture2D diffuseTexture: register(t0);

float2 screenToClip(float2 pos) {
    return pos / viewportSize * 2 - 1;
}

ScreenPixel vertexMain(ScreenVertex input) {
    ScreenPixel output;

    float2 rectPos = float2(position.x, viewportSize.y - position.y);
    float2 pos = screenToClip(input.position.xy * size + rectPos);
    output.position = float4(pos, input.position.z, 1);
    output.texCoord = input.position.xy;

    return output;
}

float4 pixelMain(ScreenPixel input): SV_Target {
    float2 rectCenter = input.position.xy + float2(-size.x / 2, size.y / 2) - position;
    float d = sdRoundedRect(rectCenter, size / 2, cornerRadius);
    if (d <= 0.0) {
        return lerp(backgroundColor, borderColor, smoothstep(-borderWidth - 0.1f, -borderWidth, d));
    } else {
        return 0;
    }
}
