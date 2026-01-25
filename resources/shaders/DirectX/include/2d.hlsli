#ifndef _2D_HLSLI
#define _2D_HLSLI

#include <common.hlsli>
#include <sdf.hlsli>

#define transparencyEnabled true
#define cullMode CULL_MODE_NONE
#define depthTestEnabled false

struct Vertex2D {
    float3 position: POSITION;
};

struct Pixel2D {
    float4 position: SV_POSITION;
    float2 texCoord: TEXCOORD0;
};

#endif