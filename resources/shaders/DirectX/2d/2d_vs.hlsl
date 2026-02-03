#include <common.hlsli>
#include <2d.hlsli>

cbuffer vertexConstants: register(b0) {
    float2 position = float2(300, 300);
    float2 size = float2(300, 300);
    matrix viewProjection;
}

Pixel2D vertexMain(Vertex2D input) {
    Pixel2D output;

    float4 inputPos = float4(input.position, 1) * float4(size, 0, 1) + float4(position, 0, 0);
    float4 outputPos = mul(inputPos, viewProjection);
    output.position = outputPos;
    output.texCoord = input.position.xy;

    return output;
}
