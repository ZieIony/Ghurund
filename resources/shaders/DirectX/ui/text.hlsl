#include <common.hlsli>
#include <ui.hlsli>
#include <sdf.hlsli>

#define transparencyEnabled

cbuffer perCamera: register(b0) {
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 350);
    float2 size = float2(300, 300);
    float4 backgroundColor = float4(0,0,0,0.15f);
    float4 borderColor;
    float4 cornerRadius = float4(4, 4, 4, 4);
    float borderWidth = 1;
}

SamplerState linearSampler: register(s0);
Texture2D colorTexture: register(t0);

UIPixel vertexMain(TextVertex input) {
    UIPixel output;

    float2 rectPos = float2(position.x, viewportSize.y - position.y);
    float2 pos = screenToClip(input.position.xy * size + rectPos, viewportSize);
    output.position = float4(pos, input.position.z, 1);
    output.texCoord = input.texCoord;

    return output;
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

uniform float pxRange = 8; // set to distance field's pixel range
uniform float4 black = float4(0, 0, 0, 1);

float screenPxRange(float2 texCoord) {
    int2 textureSize;
    colorTexture.GetDimensions(textureSize.x, textureSize.y);
    float2 unitRange = float2(pxRange, pxRange) / textureSize;
    float2 screenTexSize = float2(1.0, 1.0) / fwidth(texCoord);
    return max(0.5 * dot(unitRange, screenTexSize), 1.0);
}

float msdfText(float3 msd, float2 texCoord) {
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange(texCoord) * (sd - 0.5);
    return clamp(screenPxDistance + 0.5, 0.0, 1.0);
}

float4 pixelMain(UIPixel input): SV_Target {
    float3 msd = colorTexture.Sample(linearSampler, input.texCoord).rgb;
    float opacity = msdfText(msd, input.texCoord);
    return lerp(backgroundColor, black, opacity);
}
