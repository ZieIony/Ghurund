#pragma once

#include "graphics/Graphics.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include <wrl.h>

namespace Ghurund {
    using namespace DirectX;
    using namespace Microsoft::WRL;

    struct ScreenVertex {
        XMFLOAT3 position;
        XMFLOAT2 texCoord;

        ScreenVertex() {}

        ScreenVertex(XMFLOAT3 position, XMFLOAT2 texCoord) {
            this->position = position;
            this->texCoord = texCoord;
        }

        ScreenVertex operator+(const ScreenVertex& v)const {
            XMFLOAT3 newPos;
            XMFLOAT2 newTexCoord;
            XMStoreFloat3(&newPos, XMLoadFloat3(&position) + XMLoadFloat3(&v.position));
            XMStoreFloat2(&newTexCoord, XMLoadFloat2(&texCoord) + XMLoadFloat2(&v.texCoord));
            return ScreenVertex(newPos, newTexCoord);
        }

        ScreenVertex operator/(const float v)const {
            XMFLOAT3 newPos;
            XMFLOAT2 newTexCoord;
            XMStoreFloat3(&newPos, XMLoadFloat3(&position) / v);
            XMStoreFloat2(&newTexCoord, XMLoadFloat2(&texCoord) / v);
            return ScreenVertex(newPos, newTexCoord);
        }
    };

    struct Vertex {
        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT3 tangent;
        XMFLOAT2 texCoord;

        Vertex() {}

        Vertex(XMFLOAT3 position, XMFLOAT2 texCoord) {
            this->position = position;
            normal = XMFLOAT3(0, 1, 0);
            tangent = XMFLOAT3(1, 0, 0);
            this->texCoord = texCoord;
        }

        Vertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT2 texCoord) {
            this->position = position;
            this->normal = normal;
            tangent = XMFLOAT3(1, 0, 0);
            this->texCoord = texCoord;
        }

        Vertex operator+(const Vertex& v)const {
            XMFLOAT3 newPos, newNormal;
            XMFLOAT2 newTexCoord;
            XMStoreFloat3(&newPos, XMLoadFloat3(&position) + XMLoadFloat3(&v.position));
            XMStoreFloat3(&newNormal, XMVector3Normalize(XMLoadFloat3(&normal) + XMLoadFloat3(&v.normal)));
            XMStoreFloat2(&newTexCoord, XMLoadFloat2(&texCoord) + XMLoadFloat2(&v.texCoord));
            return Vertex(newPos, newNormal, newTexCoord);
        }

        Vertex operator/(const float v)const {
            XMFLOAT3 newPos;
            XMFLOAT2 newTexCoord;
            XMStoreFloat3(&newPos, XMLoadFloat3(&position) / v);
            XMStoreFloat2(&newTexCoord, XMLoadFloat2(&texCoord) / v);
            return Vertex(newPos, normal, newTexCoord);
        }

        bool equals(const Vertex& v, float posEpsilon, float angleEpsilon, float texCoordEpsilon) {
            float posLength, normalLength, texCoorLength;
            XMStoreFloat(&posLength, XMVector3Length(XMLoadFloat3(&position) - XMLoadFloat3(&v.position)));
            XMStoreFloat(&normalLength, XMVector3AngleBetweenNormals(XMLoadFloat3(&normal), XMLoadFloat3(&v.normal)));
            XMStoreFloat(&texCoorLength, XMVector3Length(XMLoadFloat2(&texCoord) - XMLoadFloat2(&v.texCoord)));
            return posLength < posEpsilon && normalLength < angleEpsilon && texCoorLength < texCoordEpsilon;
        }
    };

}