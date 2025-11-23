#include <common.hlsli>
#include <ui.hlsli>
#include <sdf.hlsli>

cbuffer perCamera: register(b0) {
    int2 mousePos;
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 50);
    float2 size = float2(250, 100);
}

cbuffer shadowParams: register(b2) {
    float elevation = 20;
    float alpha = 1;
    float4 color = float4(0, 0, 0, 0.5);
    float4 cornerRadius = float4(4, 4, 4, 4);
}

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 dir = (input.position.xy + float2(-0.5, 0.5)) * 2;
    float2 pos = screenToClip(input.position.xy * size + dir * elevation + mousePos, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = output.position.xy;

    return output;
}

float4 pixelMain(UIPixel input): SV_Target {
    float2 sizeDiv2 = size / 2;
    float2 rectCenter = input.position.xy + float2(-sizeDiv2.x, sizeDiv2.y) - mousePos;
    float dist = sdRoundedRect(rectCenter, sizeDiv2, cornerRadius);
    if (dist > 0.0) {
        float2 shadowRectCenter = input.position.xy + float2(-sizeDiv2.x, sizeDiv2.y - elevation / 3) - mousePos;
        float shadowDist = sdRoundedRect(shadowRectCenter, sizeDiv2 - elevation / 3, cornerRadius);
        float shadowIntensity = smoothstep(0, 1, (elevation - shadowDist) / elevation);
        float ambientShadowIntensity = smoothstep(0, 1, (elevation / 2 - dist) / elevation / 2);
        return float4(color.rgb, alpha * color.a * (shadowIntensity + ambientShadowIntensity) / 2);
    } else {
        return float4(1, 1, 1, alpha);
    }
}
