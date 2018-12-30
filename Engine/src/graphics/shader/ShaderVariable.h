#pragma once

namespace Ghurund {
    struct ShaderVariable {
        char *name = nullptr;
        size_t size, offset;

        ShaderVariable(const char *name, size_t size, size_t offset) {
            this->name = copyStr(name);
            this->size = size;
            this->offset = offset;
        }

        ~ShaderVariable() {
            delete[] name;
        }
    };
}