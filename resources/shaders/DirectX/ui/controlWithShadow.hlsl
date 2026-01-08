#include <common.hlsli>
#include <ui.hlsli>
#include <sdf.hlsli>
#include <colors.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 50);
    float2 size = float2(250, 100);
    float4 backgroundColor = float4(0.5, 0, 0, 1);
    float4 borderColor;
    float4 cornerRadius = float4(4, 4, 4, 4);
    float focused = 0.0f;
    float enabled = 0.0f;
    float borderWidth = 0, alpha = 1.0f;
}

cbuffer shadowParams: register(b2) {
    float elevation = 8;
    float4 shadowColor = float4(0, 0, 0, 0.5);
}

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 dir = (input.position.xy - 0.5) * 2;
    float2 pos = screenToClip(input.position.xy * size + dir * elevation + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = output.position.xy;

    return output;
}

float4 pixelMain(UIPixel input): SV_Target {
    float2 sizeDiv2 = size / 2;
    float2 rectCenter = input.position.xy - sizeDiv2 - position;
    float dist = sdRoundedRect(rectCenter, sizeDiv2, cornerRadius);
    if (dist > 0.0) {
        float2 shadowRectCenter = input.position.xy - float2(sizeDiv2.x, sizeDiv2.y + elevation / 3) - position;
        float shadowDist = sdRoundedRect(shadowRectCenter, sizeDiv2 - elevation / 3, cornerRadius);
        float shadowIntensity = smoothstep(0, 1, (elevation - shadowDist) / elevation);
        float ambientShadowIntensity = smoothstep(0, 1, (elevation / 2 - dist) / elevation / 2);
        return float4(shadowColor.rgb, backgroundColor.a * shadowColor.a * (shadowIntensity + ambientShadowIntensity) / 2 * alpha);
    } else {
        float4 color = saturate(mul(backgroundColor, makeBrightnessMatrix(1 + focused / 2)));
        color = saturate(mul(color, makeSaturationMatrix(enabled / 2 + 0.5)));
        return float4(color.rgb, backgroundColor.a * alpha);
    }
}
