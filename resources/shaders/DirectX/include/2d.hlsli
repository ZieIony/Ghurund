#ifndef _2D_HLSLI
#define _2D_HLSLI

#include <objectParameters.hlsli>

struct DefaultVertex2D {
    float2 position: POSITION;
    float2 texCoord: TEXCOORD0;
    uint objectId: OBJECT_ID;
};

struct DefaultPixel2D {
    float4 position: SV_POSITION;
    float2 texCoord: TEXCOORD0;
    nointerpolation uint objectId: OBJECT_ID;
};

DefaultPixel2D vertexMain(DefaultVertex2D input, ObjectParameters objectParameters);

DefaultPixel2D vertexMain(DefaultVertex2D input) {
    ObjectParameters parameters = gh_objectParameters[input.objectId];
    DefaultPixel2D output = vertexMain(input, parameters);
    output.objectId = input.objectId;
    return output;
}

#endif
