#pragma once

#include "Ghurund.h"
#include "collection/String.h"

namespace Ghurund {

    enum class ParameterTypeValue {
        FLOAT, FLOAT2, FLOAT3, MATRIX
    };

    class ParameterType {
    private:
        ParameterTypeValue value;
        unsigned int size;

    public:
        static const ParameterType &FLOAT, &FLOAT2, &FLOAT3, &MATRIX;

        ParameterType(ParameterTypeValue value, unsigned int size) {
            this->value = value;
            this->size = size;
        }

        ParameterTypeValue getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) ParameterTypeValue Value;

        unsigned int getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) unsigned int Size;
    };

    class Parameter {
    private:
        ASCIIString name;
        const ParameterType &type;
        BYTE *value;
        unsigned int index;

        friend class ParameterManager;
        ParameterManager *manager;

    public:
        static const char *WIDTH;
        static const char *HEIGHT;

        static const char *PARTY_COLOR;
        static const char *RANDOM;

        static const char *DIRECTION;
        static const char *POSITION;
        static const char *ROTATION;
        static const char *SCALE;
        static const char *TARGET;
        static const char *UP;
        static const char *RIGHT;
        static const char *FOV;
        static const char *ZNEAR;
        static const char *ZFAR;

        static const char *WORLD;
        static const char *VIEW;
        static const char *PROJECTION;
        static const char *VIEW_PROJECTION;

        Parameter(const ASCIIString &name, const ParameterType &type):type(type) {
            this->name = name;
            this->value = ghnew BYTE[type.Size];
        }

        Parameter(const ASCIIString &name, const void *value, const ParameterType &type):type(type) {
            this->name = name;
            this->value = ghnew BYTE[type.Size];
            memcpy(this->value, value, type.Size);
        }

        ~Parameter() {
            delete[] value;
        }

        inline const ASCIIString &getName() const {
            return name;
        }

        __declspec(property(get = getName)) const ASCIIString &Name;

        const ParameterType &getType() const {
            return type;
        }

        __declspec(property(get = getType)) const ParameterType &Type;

        inline const void *getValue() const {
            return value;
        }

        void setValue(const void *value);

        __declspec(property(get = getValue, put = setValue)) const void *Value;
    };
}