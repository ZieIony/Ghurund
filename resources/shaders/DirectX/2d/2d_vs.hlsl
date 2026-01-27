#include <common.hlsli>
#include <2d.hlsli>

cbuffer vertexConstants: register(b0) {
    int2 viewportSize;
    float2 position = float2(50, 100);
    float2 size = float2(300, 300);
}

Pixel2D vertexMain(Vertex2D input) {
    Pixel2D output;

    float2 pos = screenToClip(input.position.xy * size + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = input.position.xy;

    return output;
}
