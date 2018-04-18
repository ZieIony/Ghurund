#pragma once

#include "collection/String.h"
#include "ParameterProvider.h"
#include "ParameterManager.h"
#include "collection/List.h"
#include "resource/Resource.h"
#include "core/NamedObject.h"

namespace Ghurund {
    class Entity: public Resource, public ParameterProvider, public NamedObject {
    private:
        XMFLOAT3 position = {}, rotation = {}, scale = {1,1,1};
        XMFLOAT4X4 world;

        Parameter *parameterPosition, *parameterRotation, *parameterScale, *parameterWorld;

    protected:
        List<Entity*> subentities;

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0) {
            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            return Status::NOT_IMPLEMENTED;
        }

        virtual void clean() {}

    public:
        virtual ~Entity() = default;

        virtual void initParameters(ParameterManager & parameterManager) override {
            parameterPosition = parameterManager.add(Name+Parameter::POSITION, sizeof(position));
            parameterRotation = parameterManager.add(Name+Parameter::ROTATION, sizeof(rotation));
            parameterScale = parameterManager.add(Name+Parameter::SCALE, sizeof(scale));
            parameterWorld = parameterManager.add(Name+Parameter::WORLD, sizeof(world));
        }

        virtual void fillParameters() override {
            parameterPosition->setValue(&position);
            parameterRotation->setValue(&rotation);
            parameterScale->setValue(&scale);
            XMStoreFloat4x4(&world, XMMatrixScaling(scale.x, scale.y, scale.z)*XMMatrixRotationRollPitchYaw(rotation.y, rotation.x, rotation.z)*XMMatrixTranslation(position.x, position.y, position.z));
            parameterWorld->setValue(&world);
        }

        virtual void setName(const String &name) override {
            NamedObject::setName(name);
            /*if(parameterPosition!=nullptr) {  // TODO: update parameter names
                parameterPosition->setName
            }*/
        }

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

        List<Entity*> &getSubentities() {
            return subentities;
        }
    };
}