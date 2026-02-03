#ifndef _2D_HLSLI
#define _2D_HLSLI

#include <common.hlsli>
#include <sdf.hlsli>

struct Vertex2D {
    float3 position: POSITION;
};

struct Pixel2D {
    float4 position: SV_POSITION;
    float2 texCoord: TEXCOORD0;
};

#endif