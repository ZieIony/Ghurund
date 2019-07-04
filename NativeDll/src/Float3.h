#pragma once

#include <DirectXMath.h>

using namespace DirectX;

struct Int2 {
    int x, y;
};

struct Float2 {
    float x, y;
};

struct Float3 {
    float x, y, z;
};

struct Float4 {
    float x, y, z, w;
};

struct Matrix {
    float a00, a01, a02, a03;
    float a10, a11, a12, a13;
    float a20, a21, a22, a23;
    float a30, a31, a32, a33;
};

XMINT2 convertInt2(const Int2 &int2);
Int2 convertInt2(const XMINT2 &xmInt2);

XMFLOAT2 convertFloat2(const Float2 &float2);
Float2 convertFloat2(const XMFLOAT2 &xmFloat2);

XMFLOAT3 convertFloat3(const Float3 &float3);
Float3 convertFloat3(const XMFLOAT3 &xmFloat3);

XMFLOAT4X4 convertMatrix(const Matrix &matrix);
Matrix convertMatrix(const XMFLOAT4X4 &xmFloat4x4);

XMFLOAT4 convertFloat4(const Float4 &float4);
Float4 convertFloat4(const XMFLOAT4 &xmFloat4);
