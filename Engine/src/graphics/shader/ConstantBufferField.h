#pragma once

#include "core/string/AString.h"

namespace Ghurund {
    struct ConstantBufferField {
        AString name;
        size_t size, offset;

        ConstantBufferField(const AString& name, size_t size, size_t offset) {
            this->name = name;
            this->size = size;
            this->offset = offset;
        }
    };
}