#include <common.hlsli>
#include <ui.hlsli>
#include <sdf.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 350);
    float2 size = float2(300, 300);
    float4 backgroundColor = float4(0.5, 0, 0, 1);
    float4 borderColor;
    float4 cornerRadius = float4(4, 4, 4, 4);
    float borderWidth = 0;
}

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 pos = screenToClip(input.position.xy * size + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = output.position.xy;

    return output;
}

float4 pixelMain(UIPixel input): SV_Target {
    float2 sizeDiv2 = size / 2;
    float2 rectCenter = input.position.xy - sizeDiv2 - position;
    float dist = sdRoundedRect(rectCenter, sizeDiv2, cornerRadius);
    if (dist <= 0.0) {
        return lerp(backgroundColor, borderColor, smoothstep(-borderWidth - 0.1f, -borderWidth, dist));
    } else {
        return 0;
    }
}
