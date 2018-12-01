#pragma once

#include "game/parameter/ParameterProvider.h"
#include "resource/ResourceManager.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class TransformedObject {
    protected:
        XMFLOAT3 position = {}, rotation = {}, scale = {1,1,1};
        XMFLOAT4X4 world;

    public:

        virtual ~TransformedObject() = default;

        XMFLOAT4X4 getTransformation() {
            XMStoreFloat4x4(&world, XMMatrixScaling(scale.x, scale.y, scale.z)*XMMatrixRotationRollPitchYaw(rotation.y, rotation.x, rotation.z)*XMMatrixTranslation(position.x, position.y, position.z));
            return world;
        }

#pragma region transformations

        void setPosition(const XMFLOAT3 &pos) {
            this->position = pos;
        }

        void setPosition(float x, float y, float z) {
            this->position.x = x;
            this->position.y = y;
            this->position.z = z;
        }

        inline XMFLOAT3 &getPosition() {
            return position;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 &Position;

        void setRotation(const XMFLOAT3 &rotation) {
            this->rotation = rotation;
        }

        void setRotation(float yaw, float pitch, float roll) {
            this->rotation.x = yaw;
            this->rotation.y = pitch;
            this->rotation.z = roll;
        }

        inline XMFLOAT3 &getRotation() {
            return rotation;
        }

        __declspec(property(get = getRotation, put = setRotation)) XMFLOAT3 &Rotation;

        void setScale(const XMFLOAT3 &scale) {
            this->scale = scale;
        }

        void setScale(float x, float y, float z) {
            this->scale.x = x;
            this->scale.y = y;
            this->scale.z = z;
        }

        inline XMFLOAT3 &getScale() {
            return scale;
        }

        __declspec(property(get = getScale, put = setScale)) XMFLOAT3 &Scale;

#pragma endregion
    };
}