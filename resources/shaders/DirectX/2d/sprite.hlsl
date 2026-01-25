#include <common.hlsli>
#include <2d.hlsli>
#include <sdf.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 100);
    float2 size = float2(300, 300);
    float alpha = 1.0f;
}

SamplerState linearSampler: register(s0);
Texture2D colorTexture: register(t0);

Pixel2D vertexMain(Vertex2D input) {
    Pixel2D output;

    float2 pos = screenToClip(input.position.xy * size + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = input.position.xy;

    return output;
}

float4 pixelMain(Pixel2D input): SV_Target {
    float4 color = colorTexture.Sample(linearSampler, input.texCoord);
    return float4(color.rgb, color.a * alpha);
}
