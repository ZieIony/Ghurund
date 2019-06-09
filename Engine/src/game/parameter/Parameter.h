#pragma once

#include "Ghurund.h"
#include "collection/String.h"
#include "editor/ObservableObject.h"
#include "ParameterType.h"
#include "core/Pointer.h"
#include "core/Enum.h"

namespace Ghurund {
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

        ParameterId(ParameterIdEnum value, const tchar *name, const char* constantName, const ParameterType& type):Enum<ParameterIdEnum, ParameterId>(value, name), type(type) {
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

    class Parameter: public Pointer, public ObservableObject {
    protected:
        const char* constantName;
        const ParameterType& type;
        bool empty;

    public:
        Parameter(const char* constantName, const ParameterType& type):type(type) {
            this->constantName = copyStr(constantName);
        }

        ~Parameter() {
            delete[] constantName;
        }

        const ParameterType& getValueType() const {
            return type;
        }

        __declspec(property(get = getValueType)) const ParameterType& ValueType;

        const char* getConstantName() const {
            return constantName;
        }

        __declspec(property(get = getConstantName)) const char* ConstantName;

        bool isEmpty() const {
            return empty;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}