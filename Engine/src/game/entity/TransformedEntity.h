#pragma once

#include "Entity.h"

namespace Ghurund {

    class TranslatedEntity:public Entity {
    protected:
        XMFLOAT3 position = {};

        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            __super::loadInternal(context, workingDir, stream, options);
            position = stream.read<XMFLOAT3>();
            return Status::OK;
        }

        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            __super::saveInternal(context, workingDir, stream, options);
            stream.write<XMFLOAT3>(position);
            return Status::OK;
        }

    public:

        virtual XMFLOAT4X4& getTransformation() const override {
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

        inline const XMFLOAT3& getPosition() const {
            return position;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3& Position;

#pragma endregion
    };

    class TransformedEntity:public TranslatedEntity {
    protected:
        XMFLOAT3 rotation = {}, scale = {1,1,1};

        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            __super::loadInternal(context, workingDir, stream, options);
            rotation = stream.read<XMFLOAT3>();
            scale = stream.read<XMFLOAT3>();
            return Status::OK;
        }

        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            __super::saveInternal(context, workingDir, stream, options);
            stream.write<XMFLOAT3>(rotation);
            stream.write<XMFLOAT3>(scale);
            return Status::OK;
        }

    public:

        virtual XMFLOAT4X4& getTransformation() const override {
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

        inline const XMFLOAT3& getRotation() const {
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

        inline const XMFLOAT3& getScale() const {
            return scale;
        }

        __declspec(property(get = getScale, put = setScale)) XMFLOAT3& Scale;

#pragma endregion
    };
}