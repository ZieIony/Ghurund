#include <common.hlsli>
#include <3d.hlsli>

float4 pixelMain(DefaultPixel3D input): SV_Target {
    float depthNormalized = input.screenPosition.z / input.screenPosition.w;
    return float4(depthNormalized.xxx, 1);
}
