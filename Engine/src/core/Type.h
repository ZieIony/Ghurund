#pragma once

#include "Ghurund.h"
#include <functional>

namespace Ghurund {
    class Type {
    private:
        std::function<void*()> constructor;
        const tchar *name;
        unsigned int value;

        static const Type* values[10];

    public:
        static const Type &LIGHT, &CAMERA,
            &SCENE,
            &SHADER, &TEXTURE, &MATERIAL, &IMAGE,
            &MODEL, &MESH,
            &SOUND;

        Type(std::function<void*()> constructor, const tchar *name, unsigned int value) {
            this->constructor = constructor;
            this->name = name;
            this->value = value;
        }

        void *newInstance() const {
            return constructor();
        }

        const tchar *getName() const {
            return name;
        }

        __declspec(property(get = getName)) const tchar *Name;

        unsigned int getValue() const {
            return value;
        }
 
        __declspec(property(get = getValue)) unsigned int Value;

        static const Type** getValues() {
            return values;
        }

        static const size_t getValueCount() {
            return sizeof(values)/sizeof(values[0]);
        }
    };
}