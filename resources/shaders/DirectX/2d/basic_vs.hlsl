#include <globalParameters.hlsli>
#include <common.hlsli>
#include <2d.hlsli>

cbuffer vertexConstants: register(b1) {
    matrix gh_world;
}

DefaultPixel2D vertexMain(DefaultVertex2D input) {
    DefaultPixel2D output;

    float4 inputPos = float4(input.position, 0, 1);
    output.position = mul(mul(inputPos, gh_world), gh_viewProjection);
    output.texCoord = input.texCoord;

    return output;
}
