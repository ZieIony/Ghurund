#include <../common.hlsli>
#include <sdf.hlsli>

#define transparencyEnabled
#define cull_none

struct UiVertex {
    float3 position: POSITION;
};

struct TextVertex {
    float3 position: POSITION;
    float2 texCoord: TEXCOORD0;
};

struct UiPixel {
    float4 position: SV_POSITION;
    float2 texCoord: TEXCOORD0;
};

cbuffer perCamera: register(b0) {
    int2 mousePos;
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 350);
    float2 size = float2(300, 300);
    float4 backgroundColor;
    float4 borderColor;
    float4 cornerRadius = float4(4, 4, 4, 4);
    float borderWidth = 1;
}

ScreenPixel vertexMain(ScreenVertex input) {
    ScreenPixel output;

    float2 rectPos = float2(position.x, viewportSize.y - position.y);
    float2 pos = screenToClip(input.position.xy * size + rectPos, viewportSize);
    output.position = float4(pos, input.position.z, 1);
    output.texCoord = float2(input.position.x, 1-input.position.y);

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
