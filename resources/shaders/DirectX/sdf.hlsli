#ifndef SDF_HLSLI
#define SDF_HLSLI

float sdCircle(float2 pos, float radius) {
    return length(pos) - radius;
}

float sdRoundedRect(float2 p, float2 b, float4 r) {
    r.xy = (p.x > 0.0) ? r.xy : r.zw;
    r.x = (p.y > 0.0) ? r.x : r.y;
    float2 q = abs(p) - b + r.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

#endif