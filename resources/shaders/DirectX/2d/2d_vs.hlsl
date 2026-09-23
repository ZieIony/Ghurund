#include <common.hlsli>
#include <2d.hlsli>

cbuffer vertexConstants: register(b0) {
    matrix gh_world;
    matrix gh_viewProjection;
}

Pixel2D vertexMain(Vertex2D input) {
    Pixel2D output;

    float4 inputPos = float4(input.position, 0, 1);
    output.position = mul(mul(inputPos, gh_world), gh_viewProjection);
    output.texCoord = input.texCoord;

    return output;
}
