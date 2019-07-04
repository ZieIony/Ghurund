#pragma once

#include "core/StaticClass.h"
#include "graphics/entity/Camera.h"

namespace Ghurund {
    class CameraUtils:public StaticClass {
    public:

        static void lookAtEntity(Camera& camera, Entity& entity) {
            XMFLOAT3 pos;
            XMStoreFloat3(&pos, XMLoadFloat3(&entity.BoundingBox->Center) + XMLoadFloat3(&entity.BoundingBox->Extents) * 2);
            pos.z *= -1;
            pos.y /= 2;
            camera.setPositionTargetUp(pos, entity.BoundingBox->Center);
        }

        static XMFLOAT3 screenVectorTo3D(XMFLOAT2& mouseMove, Camera& camera) {
            XMMATRIX matrixInv = XMLoadFloat4x4(&camera.ViewProjectionInv);
            if (XMMatrixIsInfinite(matrixInv))
                return XMFLOAT3();

            XMVECTOR moveVec = XMLoadFloat3(&XMFLOAT3(mouseMove.x, mouseMove.y, 0));
            XMVECTOR moveVec3D = XMVector3TransformNormal(moveVec, matrixInv);

            XMFLOAT3 moveFloat3;
            XMStoreFloat3(&moveFloat3, moveVec3D);
            return moveFloat3;
        }
    };
}