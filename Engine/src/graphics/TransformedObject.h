#pragma once

#include "resource/ResourceManager.h"
#include "game/ParameterProvider.h"
#include "BoundingBox.h"

namespace Ghurund {

    class TransformedObject {
    private:
        XMFLOAT3 position = {}, rotation = {}, scale = {1,1,1};
        BoundingBox boundingBox;
        XMFLOAT4X4 world;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, MemoryInputStream &stream) {
            memcpy(&position, stream.readBytes(sizeof(position)), sizeof(position));
            memcpy(&rotation, stream.readBytes(sizeof(rotation)), sizeof(rotation));
            memcpy(&scale, stream.readBytes(sizeof(scale)), sizeof(scale));

            memcpy(&boundingBox, stream.readBytes(sizeof(boundingBox)), sizeof(boundingBox));

            memcpy(&world, stream.readBytes(sizeof(world)), sizeof(world));

            return Status::OK;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream) const {
            stream.writeBytes(&position, sizeof(position));
            stream.writeBytes(&rotation, sizeof(rotation));
            stream.writeBytes(&scale, sizeof(scale));

            stream.writeBytes(&boundingBox, sizeof(boundingBox));

            stream.writeBytes(&world, sizeof(world));

            return Status::OK;
        }

        virtual void clean() {}

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

        inline const XMFLOAT3 &getPosition()const {
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

        inline const XMFLOAT3 &getRotation()const {
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

        inline const XMFLOAT3 &getScale()const {
            return scale;
        }

        __declspec(property(get = getScale, put = setScale)) XMFLOAT3 &Scale;

#pragma endregion

        BoundingBox &getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingBox &BoundingBox;
    };
}