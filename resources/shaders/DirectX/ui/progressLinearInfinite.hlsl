#include <common.hlsli>
#include <ui.hlsli>
#include <sdf.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
    float time;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 100);
    float2 size = float2(300, 5);
    float4 backgroundColor = float4(1, 1, 1, 0.15f);
    float4 progressColor = float4(1, 0, 0, 1);
    float alpha = 1.0f;
}

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 pos = screenToClip(input.position.xy * size + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = input.position.xy;

    return output;
}

float4 pixelMain(UIPixel input): SV_Target {
    float base = cos((frac(time) + 1) * PI) * 2.0f / 3.0f;
    float lx = base + 1.0f/3.0f;
    float rx = base + 2.0f/3.0f;
    float s = min(
        smoothstep(lx - 0.5f / size.x, lx + 0.5f / size.x, input.texCoord.x),
        smoothstep(rx + 0.5f / size.x, rx - 0.5f / size.x, input.texCoord.x)
    );
    float4 color = lerp(backgroundColor, progressColor, s);
    return float4(color.rgb, color.a * alpha);
}
