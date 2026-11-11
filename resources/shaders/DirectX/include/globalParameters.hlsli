#ifndef GLOBALPARAMS_HLSLI
#define GLOBALPARAMS_HLSLI

cbuffer GlobalParams: register(b0) {
    float gh_time: packoffset(c0);
    float3 gh_cameraPosition: packoffset(c0.y);
    int2 gh_mousePosition: packoffset(c1);
    int2 gh_viewportSize: packoffset(c1.z);
    matrix gh_viewProjection: packoffset(c2);
}

#endif