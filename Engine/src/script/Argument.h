#pragma once

#include "angelscript.h"

namespace Ghurund {
    class Argument {
    private:
        void* value = nullptr;

    public:
        Argument(const Argument& other) {
            value = other.value;
        }

        Argument(void* obj) {
            value = obj;
        }

        void set(asUINT index, asIScriptContext& context) const {
            context.SetArgAddress(index, value);
        }
    };
}