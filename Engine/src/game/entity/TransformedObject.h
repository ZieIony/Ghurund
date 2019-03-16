#pragma once

#include "game/parameter/ParameterProvider.h"
#include "resource/ResourceManager.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class TranslatedObject:public virtual ObservableObject {
    protected:
        XMFLOAT3 position = {};
        XMFLOAT4X4 world;

        void loadTransformation(MemoryInputStream& stream) {
            memcpy(&position, &stream.read<XMFLOAT3>(), sizeof(position));

            memcpy(&world, &stream.read<XMFLOAT4X4>(), sizeof(world));
        }

        void saveTransformation(MemoryOutputStream& stream) const {
            stream.write(position);

            stream.write(world);
        }

    public:

        virtual ~TranslatedObject() = default;

        XMFLOAT4X4 getTransformation() {
            XMStoreFloat4x4(&world, XMMatrixTranslation(position.x, position.y, position.z));
            return world;
        }

#pragma region transformations

        void setPosition(const XMFLOAT3& pos) {
            this->position = pos;
            notifyObjectChanged();
        }

        void setPosition(float x, float y, float z) {
            this->position.x = x;
            this->position.y = y;
            this->position.z = z;
            notifyObjectChanged();
        }

        inline XMFLOAT3& getPosition() {
            return position;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3& Position;

#pragma endregion
    };

    class TransformedObject:public TranslatedObject {
    protected:
        XMFLOAT3 rotation = {}, scale = {1,1,1};

        void loadTransformation(MemoryInputStream& stream) {
            memcpy(&rotation, &stream.read<XMFLOAT3>(), sizeof(rotation));
            memcpy(&scale, &stream.read<XMFLOAT3>(), sizeof(scale));
            TranslatedObject::loadTransformation(stream);
        }

        void saveTransformation(MemoryOutputStream& stream) const {
            stream.write(rotation);
            stream.write(scale);
            TranslatedObject::saveTransformation(stream);
        }

    public:

        XMFLOAT4X4 getTransformation() {
            XMStoreFloat4x4(&world, XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationRollPitchYaw(rotation.y, rotation.x, rotation.z) * XMMatrixTranslation(position.x, position.y, position.z));
            return world;
        }

#pragma region transformations

        void setRotation(const XMFLOAT3& rotation) {
            this->rotation = rotation;
            notifyObjectChanged();
        }

        void setRotation(float yaw, float pitch, float roll) {
            this->rotation.x = yaw;
            this->rotation.y = pitch;
            this->rotation.z = roll;
            notifyObjectChanged();
        }

        inline XMFLOAT3& getRotation() {
            return rotation;
        }

        __declspec(property(get = getRotation, put = setRotation)) XMFLOAT3& Rotation;

        void setScale(const XMFLOAT3& scale) {
            this->scale = scale;
            notifyObjectChanged();
        }

        void setScale(float x, float y, float z) {
            this->scale.x = x;
            this->scale.y = y;
            this->scale.z = z;
            notifyObjectChanged();
        }

        inline XMFLOAT3& getScale() {
            return scale;
        }

        __declspec(property(get = getScale, put = setScale)) XMFLOAT3& Scale;

#pragma endregion
    };
}