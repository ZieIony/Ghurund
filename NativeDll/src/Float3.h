#pragma once

#include "Ghurund.h"

struct Float3 {
    float x, y, z;
};

XMFLOAT3 convertFloat(const Float3 &float3) {
    return XMFLOAT3(float3.x, float3.y, float3.z);
}

Float3 convertFloat(const XMFLOAT3 &xmFloat3) {
    Float3 float3 = {xmFloat3.x,xmFloat3.y,xmFloat3.z};
    return float3;
}