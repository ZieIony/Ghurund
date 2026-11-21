#include <globalParameters.hlsli>
#include <objectParameters.hlsli>
#include <common.hlsli>
#include <2d.hlsli>

DefaultPixel2D vertexMain(DefaultVertex2D input, ObjectParameters objectParameters) {
    DefaultPixel2D output;

    output.position = float4(input.position, 0, 1);
    output.texCoord = input.texCoord;

    return output;
}
