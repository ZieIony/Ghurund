#ifndef SDF_HLSLI
#define SDF_HLSLI

float sdCircle(float2 pos, float radius) {
    return length(pos) - radius;
}

float sdRect(float2 p, float2 b) {
    float2 q = abs(p) - b;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0));
}

float sdRoundedRect(float2 p, float2 b, float4 r) {
    r.xy = (p.x > 0.0) ? r.xy : r.zw;
    r.x = (p.y > 0.0) ? r.x : r.y;
    float2 q = abs(p) - b + r.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

float sdRing(float2 p, float2 n, float r, float th) {
    p.x = abs(p.x);
    p = mul(float2x2(n.x, n.y, -n.y, n.x), p);
    return max(
        abs(length(p) - r) - th * 0.5,
        length(float2(p.x, max(0.0, abs(r - p.y) - th * 0.5))) * sign(p.x)
    );
}

float sdCapsule(float2 p, float2 b, float radius) {
    return sdRect(p, b) - radius;
}

#endif