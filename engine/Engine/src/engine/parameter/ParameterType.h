#pragma once

#include "core/Enum.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    enum class ParameterTypeEnum {
        INT, INT2, FLOAT, FLOAT2, FLOAT3, MATRIX, COLOR, TEXTURE
    };

    class ParameterType:public Enum<ParameterTypeEnum, ParameterType> {
    private:
        uint32_t size;

        ParameterType(ParameterTypeEnum value, const char* name, uint32_t size):Enum<ParameterTypeEnum, ParameterType>(value, name), size(size) {}

    public:
        static const ParameterType INT, INT2, FLOAT, FLOAT2, FLOAT3, MATRIX, COLOR, TEXTURE;

        uint32_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) uint32_t Size;

        static const ParameterType &fromSize(uint32_t size) {
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