#pragma once

namespace Ghurund {

    enum class ParameterTypeEnum {
        INT, INT2, FLOAT, FLOAT2, FLOAT3, MATRIX, COLOR, TEXTURE
    };

    class ParameterType {
    private:
        ParameterTypeEnum value;
        unsigned int size;

    public:
        static const ParameterType& INT, & INT2, & FLOAT, & FLOAT2, & FLOAT3, & MATRIX, & COLOR, & TEXTURE;

        ParameterType(ParameterTypeEnum value, unsigned int size) {
            this->value = value;
            this->size = size;
        }

        ParameterTypeEnum getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) ParameterTypeEnum Value;

        unsigned int getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) unsigned int Size;
    };
}