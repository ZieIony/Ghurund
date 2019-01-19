#include "Float3.h"

XMINT2 convertInt2(const Int2 &int2) {
    return XMINT2(int2.x, int2.y);
}

Int2 convertInt2(const XMINT2 &xmInt2) {
    Int2 int2 = {xmInt2.x, xmInt2.y};
    return int2;
}

XMFLOAT2 convertFloat2(const Float2 &float2) {
    return XMFLOAT2(float2.x, float2.y);
}

Float2 convertFloat2(const XMFLOAT2 &xmFloat2) {
    Float2 float2 = {xmFloat2.x, xmFloat2.y};
    return float2;
}

XMFLOAT3 convertFloat3(const Float3 &float3) {
    return XMFLOAT3(float3.x, float3.y, float3.z);
}

Float3 convertFloat3(const XMFLOAT3 &xmFloat3) {
    Float3 float3 = {xmFloat3.x, xmFloat3.y, xmFloat3.z};
    return float3;
}

XMFLOAT4X4 convertMatrix(const Matrix &matrix) {
    return XMFLOAT4X4(matrix.a00, matrix.a01, matrix.a02, matrix.a03,
                      matrix.a10, matrix.a11, matrix.a12, matrix.a13,
                      matrix.a20, matrix.a21, matrix.a22, matrix.a23,
                      matrix.a30, matrix.a31, matrix.a32, matrix.a33);
}

Matrix convertMatrix(const XMFLOAT4X4 &xmFloat4x4) {
    Matrix matrix = {xmFloat4x4._11,xmFloat4x4._12,xmFloat4x4._13,xmFloat4x4._14,
        xmFloat4x4._21,xmFloat4x4._22,xmFloat4x4._23,xmFloat4x4._24,
        xmFloat4x4._31,xmFloat4x4._32,xmFloat4x4._33,xmFloat4x4._34,
        xmFloat4x4._41,xmFloat4x4._42,xmFloat4x4._43,xmFloat4x4._44};
    return matrix;
}