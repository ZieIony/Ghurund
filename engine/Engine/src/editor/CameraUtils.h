#pragma once

#include "game/entity/camera/Camera.h"
#include "graphics/DrawableComponent.h"

namespace Ghurund {
    class CameraUtils {
	private:
		CameraUtils() = delete;

    public:
        static void lookAtEntity(Camera& camera, DrawableComponent& entity) {
            /*XMFLOAT3 pos;
            XMStoreFloat3(&pos, XMLoadFloat3(&entity.BoundingBox->Center) + XMLoadFloat3(&entity.BoundingBox->Extents) * 2);
            pos.z *= -1;
            pos.y /= 2;
            camera.setPositionTargetUp(pos, entity.BoundingBox->Center);*/
        }

        static XMFLOAT3 screenVectorTo3D(XMFLOAT2& mouseMove, Camera& camera) {
            XMMATRIX matrixInv = XMLoadFloat4x4(&camera.ViewProjectionInv);
            if (XMMatrixIsInfinite(matrixInv))
                return XMFLOAT3();

            XMFLOAT3 moveVec = { mouseMove.x, mouseMove.y, 0 };
            XMVECTOR moveVec3D = XMVector3TransformNormal(XMLoadFloat3(&moveVec), matrixInv);

            XMFLOAT3 moveFloat3;
            XMStoreFloat3(&moveFloat3, moveVec3D);
            return moveFloat3;
        }
    };
}