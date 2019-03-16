#pragma once

#include "Ghurund.h"
#include <functional>

namespace Ghurund {
    class Type {
    private:
        std::function<void*()> constructor;
        const char *name;

        Type() = default;

    public:
        static const Type &LIGHT, &CAMERA,
            &SCENE,
            &SHADER, &TEXTURE, &MATERIAL, &IMAGE,
            &MODEL, &MESH,
            &SOUND,
            &COMMAND_LIST,
            &SCRIPT,
            
            &TIMER;

        Type(std::function<void*()> constructor, const char *name) {
            this->constructor = constructor;
            this->name = name;
        }

        void *newInstance() const {
            return constructor();
        }

        const char *getName() const {
            return name;
        }

        __declspec(property(get = getName)) const char *Name;

        bool operator==(const Type &type) const {
            return this==&type;
        }

        bool operator==(const Type &type) {
            return this==&type;
        }
    };
}