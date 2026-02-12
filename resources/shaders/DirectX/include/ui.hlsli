#ifndef UI_HLSLI
#define UI_HLSLI

#include <common.hlsli>
#include <sdf.hlsli>

#define transparencyEnabled true
#define cullMode CULL_MODE_NONE
#define depthTestEnabled false

struct UIVertex {
    float2 position: POSITION;
};

struct TextVertex {
    float3 position: POSITION;
    float2 texCoord: TEXCOORD0;
};

struct UIPixel {
    float4 position: SV_POSITION;
    float2 texCoord: TEXCOORD0;
};

#endif