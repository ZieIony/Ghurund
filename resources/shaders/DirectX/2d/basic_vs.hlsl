#include <globalParameters.hlsli>
#include <objectParameters.hlsli>
#include <common.hlsli>
#include <2d.hlsli>

DefaultPixel2D vertexMain(DefaultVertex2D input, ObjectParameters objectParameters) {
    DefaultPixel2D output;

    float4 inputPos = float4(input.position, 0, 1);
    output.position = mul(mul(inputPos, objectParameters.world), gh_viewProjection);
    output.texCoord = input.texCoord;

    return output;
}
