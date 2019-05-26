#pragma once

#include "Ghurund.h"
#include "collection/String.h"
#include "editor/ObservableObject.h"
#include "ParameterType.h"
#include "core/Pointer.h"

namespace Ghurund {
    namespace ParameterId {
        enum Type {
            VIEWPORT_SIZE, OUTLINE_COLOR,
            PARTY_COLOR, RANDOM, AMBIENT_LIGHT,
            POSITION, ROTATION, SCALE,
            CAMERA_DIRECTION, CAMERA_POSITION, CAMERA_TARGET, CAMERA_UP, CAMERA_RIGHT,
            FOV, ZNEAR, ZFAR,
            WORLD, WORLD_IT, VIEW, PROJECTION, VIEW_PROJECTION
        };
    }

    class Parameter: public Pointer, public ObservableObject {
    protected:
        ASCIIString name;
        const ParameterType& type;

    public:
        Parameter(const ASCIIString& name, const ParameterType& type):type(type) {
            this->name = name;
        }

        inline const ASCIIString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const ASCIIString& Name;

        const ParameterType& getValueType() const {
            return type;
        }

        __declspec(property(get = getValueType)) const ParameterType& ValueType;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

}