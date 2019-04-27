#pragma once

#include "Ghurund.h"
#include "collection/String.h"
#include "editor/ObservableObject.h"
#include "ParameterType.h"

namespace Ghurund {

    class Parameter: public ObservableObject {
    protected:
        ASCIIString name;
        const ParameterType& type;

    public:
        static const char* VIEWPORT_SIZE;

        static const char* PARTY_COLOR;
        static const char* RANDOM;
        static const char* AMBIENT_LIGHT;

        static const char* POSITION;
        static const char* ROTATION;
        static const char* SCALE;

        static const char* CAMERA_DIRECTION;
        static const char* CAMERA_POSITION;
        static const char* CAMERA_TARGET;
        static const char* CAMERA_UP;
        static const char* CAMERA_RIGHT;

        static const char* FOV;
        static const char* ZNEAR;
        static const char* ZFAR;

        static const char* WORLD;
        static const char* WORLD_IT;
        static const char* VIEW;
        static const char* PROJECTION;
        static const char* VIEW_PROJECTION;

        Parameter(const ASCIIString& name, const ParameterType& type):type(type) {
            this->name = name;
        }

        inline const ASCIIString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const ASCIIString& Name;

        const ParameterType& getType() const {
            return type;
        }

        __declspec(property(get = getType)) const ParameterType& Type;
    };

}