#ifndef SDF_HLSLI
#define SDF_HLSLI

// 2D
float sdfCircle(float2 pos, float radius) {
    return length(pos) - radius;
}

float sdfRect(float2 pos, float2 b) {
    float2 q = abs(pos) - b;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0));
}

float sdfRoundedRect(float2 pos, float2 b, float4 r) {
    r.xy = (pos.x > 0.0) ? r.xy : r.zw;
    r.x = (pos.y > 0.0) ? r.x : r.y;
    float2 q = abs(pos) - b + r.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

float sdfRing(float2 pos, float2 n, float r, float th) {
    pos.x = abs(pos.x);
    pos = mul(float2x2(n.x, n.y, -n.y, n.x), pos);
    return max(
        abs(length(pos) - r) - th * 0.5,
        length(float2(pos.x, max(0.0, abs(r - pos.y) - th * 0.5))) * sign(pos.x)
    );
}

float sdfCapsule(float2 pos, float2 b, float radius) {
    float2 q = abs(pos) - b + radius;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - radius;
}

#endif