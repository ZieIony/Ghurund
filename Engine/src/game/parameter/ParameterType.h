#pragma once

namespace Ghurund {

    enum class ParameterValueTypeValue {
        INT, INT2, FLOAT, FLOAT2, FLOAT3, MATRIX, COLOR, TEXTURE
    };

    class ParameterValueType {
    private:
        ParameterValueTypeValue value;
        unsigned int size;

    public:
        static const ParameterValueType& INT, & INT2, & FLOAT, & FLOAT2, & FLOAT3, & MATRIX, & COLOR, & TEXTURE;

        ParameterValueType(ParameterValueTypeValue value, unsigned int size) {
            this->value = value;
            this->size = size;
        }

        ParameterValueTypeValue getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) ParameterValueTypeValue Value;

        unsigned int getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) unsigned int Size;
    };
}