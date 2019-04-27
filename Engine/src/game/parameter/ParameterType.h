#pragma once

namespace Ghurund {

    enum class ParameterTypeValue {
        INT, INT2, FLOAT, FLOAT2, FLOAT3, MATRIX, COLOR, OBJECT
    };

    class ParameterType {
    private:
        ParameterTypeValue value;
        unsigned int size;

    public:
        static const ParameterType& INT, & INT2, & FLOAT, & FLOAT2, & FLOAT3, & MATRIX, & COLOR, & OBJECT;

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
}