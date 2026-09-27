#ifndef _2D_HLSLI
#define _2D_HLSLI

struct DefaultVertex2D {
    float2 position: POSITION;
    float2 texCoord: TEXCOORD0;
};

struct DefaultPixel2D {
    float4 position: SV_POSITION;
    float2 texCoord: TEXCOORD0;
};

#endif