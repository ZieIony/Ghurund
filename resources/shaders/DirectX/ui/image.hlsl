#include <common.hlsli>
#include <ui.hlsli>
#include <sdf.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 350);
    float2 size = float2(300, 300);
}

SamplerState linearSampler: register(s0);
Texture2D image: register(t0);

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 pos = screenToClip(input.position.xy * size + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = output.position.xy;

    return output;
}

float4 pixelMain(UIPixel input): SV_Target {
    return image.Sample(linearSampler, input.texCoord);
}
