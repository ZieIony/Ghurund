#pragma once

namespace Ghurund {
    struct ConstantBufferField {
        char *name = nullptr;
        size_t size, offset;

        ConstantBufferField(const char *name, size_t size, size_t offset) {
            this->name = copyStr(name);
            this->size = size;
            this->offset = offset;
        }

        ~ConstantBufferField() {
            delete[] name;
        }
    };
}