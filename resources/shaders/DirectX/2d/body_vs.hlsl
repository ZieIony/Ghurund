#include <common.hlsli>
#include <2d.hlsli>

cbuffer vertexConstants: register(b0) {
    matrix world;
    matrix viewProjection;
}

Pixel2D vertexMain(Vertex2D input) {
    Pixel2D output;

    float4 inputPos = float4(input.position, 0, 1);
    output.position = mul(mul(inputPos, world), viewProjection);
    output.texCoord = input.texCoord;

    return output;
}
