#include <common.hlsli>
#include <3d.hlsli>

float4 pixelMain(DefaultPixel3D input): SV_Target {
    float4 color = float4(input.texCoord, 1, 1);
    return color;
}
