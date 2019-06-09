#pragma once

#include "game/parameter/ParameterProvider.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class GlobalEntity {
    private:
        XMFLOAT4X4 world;
        BoundingOrientedBox boundingBox;
        bool culled = false;

        Model& model;

    public:
        GlobalEntity(Model& model, BoundingBox& boundingBox, XMFLOAT4X4 world):model(model) {
            BoundingOrientedBox::CreateFromBoundingBox(this->boundingBox, boundingBox);
            this->boundingBox.Transform(this->boundingBox, XMLoadFloat4x4(&world));
            this->world = world;
        }

        const XMFLOAT4X4& getTransformation() const {
            return world;
        }

        __declspec(property(get = getTransformation)) XMFLOAT4X4& Transformation;

        Model& getModel() const {
            return model;
        }

        __declspec(property(get = getModel)) Model& Model;

        BoundingOrientedBox& getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingOrientedBox& BoundingBox;

        bool isCulled() {
            return culled;
        }

        __declspec(property(get = isCulled)) bool Culled;

        void cull(BoundingFrustum& frustum) {
            culled = model.CullingEnabled && frustum.Contains(boundingBox) == ContainmentType::DISJOINT;
        }

        bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
            if (boundingBox.Intersects(XMLoadFloat3(&pos), XMLoadFloat3(&dir), dist)) {
                XMMATRIX invTransform = XMMatrixInverse(nullptr, XMLoadFloat4x4(&world));
                XMFLOAT3 pos2, dir2;
                XMStoreFloat3(&pos2, XMVector3TransformCoord(XMLoadFloat3(&pos), invTransform));
                XMStoreFloat3(&dir2, XMVector3Normalize(XMVector3TransformNormal(XMLoadFloat3(&dir), invTransform)));
                return model.intersects(pos2, dir2, dist);
            }
            return false;
        }
    };
}