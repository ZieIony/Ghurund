#pragma once

#include "Common.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace Ghurund {
    template<class Type> inline Type minMax(Type a, Type b, Type c) {
        if(b < a)
            return a;
        if(b > c)
            return c;
        return b;
    }

    template<class Type> inline Type lerp(Type val1, Type val2, float fact) {
        return (1 - fact)*val1 + fact*val2;
    }

    template<class Type> inline Type round(Type a) {
        return floor(a + (Type)0.5);
    }
    template<class Type> inline Type frac(Type a) {
        float a2 = abs(a);
        return a2 - floor(a2);
    }

    inline float random() {
        return (float)rand() / (float)RAND_MAX;
    }
    /*
    float checkRayTriangle(XMFLOAT3 &pos, XMFLOAT3 &dir,
                           XMFLOAT3 &vertex0, XMFLOAT3 &vertex1, XMFLOAT3 &vertex2) {
        const float EPSILON = 0.0000001;
        XMVECTOR edge1, edge2, h, s, q;
        float f, u, v;

        XMVECTOR dv = XMLoadFloat3(&dir);
        XMVECTOR v0 = XMLoadFloat3(&vertex0);
        edge1 = XMLoadFloat3(&vertex1) - v0;
        edge2 = XMLoadFloat3(&vertex2) - v0;
        h = XMVector3Cross(dv, edge2);
        float e1HDot;
        XMStoreFloat(&e1HDot, XMVector3Dot(edge1, h));
        if(e1HDot > -EPSILON && e1HDot < EPSILON)
            return -1;    // This ray is parallel to this triangle.
        f = 1.0/e1HDot;
        s = XMLoadFloat3(&pos) - v0;
        float sHDot;
        XMStoreFloat(&sHDot, XMVector3Dot(s, h));
        u = f * sHDot;
        if(u < 0.0 || u > 1.0)
            return -1;
        q = XMVector3Cross(s, edge1);
        float dQDot;
        XMStoreFloat(&dQDot, XMVector3Dot(dv, q));
        v = f * dQDot;
        if(v < 0.0 || u + v > 1.0)
            return -1;
        // At this stage we can compute t to find out where the intersection point is on the line.
        float e2QDot;
        XMStoreFloat(&e2QDot, XMVector3Dot(edge2, q));
        return f * e2QDot;
    }

    inline float checkRayQuad(XMFLOAT3 &pos, XMFLOAT3 &dir,
                              XMFLOAT3 &vertex0, XMFLOAT3 &vertex1, XMFLOAT3 &vertex2, XMFLOAT3 &vertex3) {
        return max(checkRayTriangle(pos, dir, vertex0, vertex1, vertex2), checkRayTriangle(pos, dir, vertex0, vertex2, vertex3));
    }

    inline float checkRaySphere(XMFLOAT3& pos, XMFLOAT3& dir,
                               XMFLOAT3& center, float radius) {
        XMVECTOR m = XMLoadFloat3(&pos) - XMLoadFloat3(&center);
        XMVECTOR dv = XMLoadFloat3(&dir);
        float mDotD;
        XMStoreFloat(&mDotD, XMVector3Dot(m, dv));
        float mDotM;
        XMStoreFloat(&mDotM, XMVector3Dot(m, m));
        float c = mDotM - radius * radius;

        // Exit if r’s origin outside sphere (c > 0) and r pointing away from sphere (mDotD > 0) 
        if(c > 0.0f && mDotD > 0.0f)
            return -1;
        float discr = mDotD*mDotD - c;

        // A negative discriminant corresponds to ray missing sphere 
        if(discr < 0.0f)
            return -1;

        // Ray now found to intersect sphere, compute smallest t value of intersection
        float t = -mDotD - sqrtf(discr);

        // If t is negative, ray started inside sphere so clamp t to zero 
        if(t < 0.0f)
            t = 0.0f;

        return t;
    }*/
}