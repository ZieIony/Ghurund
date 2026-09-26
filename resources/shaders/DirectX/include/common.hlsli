#ifndef COMMON_HLSLI
#define COMMON_HLSLI

static const float PI = 3.14159265f;
static const float E = 2.71828182f;
static const float EPSILON = 0.00001f;
static const float MAX_FLOAT = 3.402823466e+38;

static const matrix MATRIX_IDENTITY = {
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 }
};

float2 screenToClip(float2 screenPos, int2 viewportSize) {
    float2 pos = screenPos / viewportSize * 2 - 1;
    return float2(pos.x, -pos.y);
}

#endif