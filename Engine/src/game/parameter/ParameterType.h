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
        static const ParameterType INT, INT2, FLOAT, FLOAT2, FLOAT3, MATRIX, COLOR, TEXTURE;

        static const EnumValues<ParameterTypeEnum, ParameterType> VALUES;

        ParameterType(ParameterTypeEnum value, const char* name, unsigned int size):Enum<ParameterTypeEnum, ParameterType>(value, name) {
            this->size = size;
        }

        unsigned int getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) unsigned int Size;

        static const ParameterType &fromSize(size_t size) {
            if (size == 4) {
                return ParameterType::FLOAT;
            } else if (size == 8) {
                return ParameterType::FLOAT2;
            } else if (size == 12) {
                return ParameterType::FLOAT3;
            } else if (size == 16) {
                return ParameterType::COLOR;
            } else {
                return ParameterType::MATRIX;
            }
        }
    };
}