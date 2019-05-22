#pragma once

#include "core/Enum.h"

namespace Ghurund {

    enum class ParameterTypeEnum {
        INT, INT2, FLOAT, FLOAT2, FLOAT3, MATRIX, COLOR, TEXTURE
    };

    class ParameterType:public Enum<ParameterTypeEnum, ParameterType> {
    private:
        unsigned int size;

    public:
        static const ParameterType& INT, & INT2, & FLOAT, & FLOAT2, & FLOAT3, & MATRIX, & COLOR, & TEXTURE;

        ParameterType(ParameterTypeEnum value, const tchar* name, unsigned int size):Enum<ParameterTypeEnum, ParameterType>(value, name) {
            this->size = size;
        }

        unsigned int getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) unsigned int Size;
    };
}