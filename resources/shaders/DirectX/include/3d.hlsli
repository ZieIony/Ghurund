#ifndef _3D_HLSLI
#define _3D_HLSLI

struct Vertex3D {
    float3 position: POSITION;
    float3 normal: NORMAL;
    float2 texCoord: TEXCOORD0;
};

struct Pixel3D {
    float4 position: SV_POSITION;
    float3 normal: NORMAL;
    float2 texCoord: TEXCOORD0;
};

#endif