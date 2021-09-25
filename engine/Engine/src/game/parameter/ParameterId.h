#pragma once

#include "ParameterType.h"
#include "core/Enum.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    enum class ParameterIdEnum {
        VIEWPORT_SIZE,
        OUTLINE_COLOR,
        PARTY_COLOR,
        RANDOM,
        AMBIENT_LIGHT,
        POSITION, ROTATION, SCALE,
        CAMERA_DIRECTION, CAMERA_POSITION, CAMERA_TARGET, CAMERA_UP, CAMERA_RIGHT,
        FOV, ZNEAR, ZFAR,
        WORLD, WORLD_IT, VIEW, PROJECTION, VIEW_PROJECTION, VIEW_PROJECTION_INV,
        DIFFUSE_TEXTURE, SPECULAR_TEXTURE, NORMAL_TEXTURE,
    };

    class ParameterId:public Enum<ParameterIdEnum, ParameterId> {
    private:
        const char* constantName;
        const ParameterType& type;

    public:
        static const ParameterId VIEWPORT_SIZE,
            OUTLINE_COLOR,
            PARTY_COLOR,
            RANDOM,
            AMBIENT_LIGHT,
            POSITION, ROTATION, SCALE,
            CAMERA_DIRECTION, CAMERA_POSITION, CAMERA_TARGET, CAMERA_UP, CAMERA_RIGHT,
            FOV, ZNEAR, ZFAR,
            WORLD, WORLD_IT, VIEW, PROJECTION, VIEW_PROJECTION, VIEW_PROJECTION_INV,
            DIFFUSE_TEXTURE, SPECULAR_TEXTURE, NORMAL_TEXTURE;

        static const EnumValues<ParameterIdEnum, ParameterId> VALUES;

        ParameterId(ParameterIdEnum value, const char* name, const char* constantName, const ParameterType& type):Enum<ParameterIdEnum, ParameterId>(value, name), type(type) {
            this->constantName = constantName;
        }

        const ParameterType& getValueType() const {
            return type;
        }

        __declspec(property(get = getValueType)) const ParameterType& ValueType;

        const char* getConstantName() const {
            return constantName;
        }

        __declspec(property(get = getConstantName)) const char* ConstantName;
    };
}