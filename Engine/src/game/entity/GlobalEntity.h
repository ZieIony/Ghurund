#pragma once

#include "game/parameter/ParameterProvider.h"

#include <DirectXCollision.h>

namespace Ghurund {

    template <class Type>
    class GlobalEntity {
    private:
        XMFLOAT4X4 world;
        BoundingOrientedBox boundingBox;
        bool visible = true;

        Type &entity;

    public:
        GlobalEntity(Type &entity, BoundingBox &boundingBox, XMFLOAT4X4 world):entity(entity) {
            BoundingOrientedBox::CreateFromBoundingBox(this->boundingBox, boundingBox);
            this->boundingBox.Transform(this->boundingBox, XMLoadFloat4x4(&world));
            this->world = world;
        }

        const XMFLOAT4X4 &getTransformation() const {
            return world;
        }

        __declspec(property(get = getTransformation)) XMFLOAT4X4 &Transformation;

        Type &getEntity() const {
            return entity;
        }

        __declspec(property(get = getEntity)) Type &Entity;

        BoundingOrientedBox &getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingOrientedBox &BoundingBox;

        bool isVisible() {
            return visible;
        }

        __declspec(property(get = isVisible)) bool Visible;

        void cull(BoundingFrustum &frustum) {
            visible = frustum.Contains(boundingBox)!=ContainmentType::DISJOINT;
        }

        bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir) {
            float dist;
            if(boundingBox.Intersects(XMLoadFloat3(&pos), XMLoadFloat3(&dir), dist)) {
                XMMATRIX invTransform = XMMatrixInverse(nullptr, XMLoadFloat4x4(&world));
                XMFLOAT3 pos2, dir2;
                XMStoreFloat3(&pos2, XMVector3TransformCoord(XMLoadFloat3(&pos), invTransform));
                XMStoreFloat3(&dir2, XMVector3Normalize(XMVector3TransformNormal(XMLoadFloat3(&dir), invTransform)));
                return entity.intersects(pos2, dir2);
            }
            return false;
        }
    };
}