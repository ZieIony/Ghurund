#pragma once

#include "Ghurund.h"
#include <functional>

namespace Ghurund {
    class Type {
    private:
        std::function<void*()> constructor;
        const tchar *name;

    public:
        static const Type &LIGHT, &CAMERA,
            &SCENE,
            &SHADER, &TEXTURE, &MATERIAL, &IMAGE,
            &MODEL, &MESH,
            &SOUND;

        Type(std::function<void*()> constructor, const tchar *name) {
            this->constructor = constructor;
            this->name = name;
        }

        void *newInstance() const {
            return constructor();
        }

        const tchar *getName() const {
            return name;
        }

        __declspec(property(get = getName)) const tchar *Name;
    };
}