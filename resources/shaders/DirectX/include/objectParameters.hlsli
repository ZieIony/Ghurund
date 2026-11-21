#ifndef PEROBJPARAMS_HLSLI
#define PEROBJPARAMS_HLSLI

struct ObjectParameters {
    float4x4 world;
};

StructuredBuffer<ObjectParameters> gh_objectParameters: register(t0);

#endif