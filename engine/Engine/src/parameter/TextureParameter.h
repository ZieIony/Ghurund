#pragma once

#include "Parameter.h"
#include "core/resource/Resource.h"
#include "core/directx/texture/Texture.h"

namespace Ghurund {
    using namespace Ghurund::Core::DirectX;

    class TextureParameter:public Parameter {
    private:
        Texture* value;
        Texture* defaultValue = nullptr;

    public:
        TextureParameter(const char* constantName):Parameter(constantName, ParameterType::TEXTURE) {
            value = nullptr;
            empty = true;
        }

        TextureParameter(const char* constantName, Texture* value):Parameter(constantName, ParameterType::TEXTURE) {
            this->value = value;
            value->addReference();
            empty = false;
        }

        ~TextureParameter() {
            if (value)
                value->release();
            if (defaultValue)
                defaultValue->release();
        }

        inline Texture* getValue() {
            return value;
        }

        void setValue(Texture* value) {
            setPointer(this->value, value);
            empty = false;
        }

        void clearValue() {
            setPointer(value, defaultValue);
            empty = true;
        }

        __declspec(property(get = getValue, put = setValue)) Texture* Value;

        inline Texture* getDefaultValue() const {
            return defaultValue;
        }

        void setDefaultValue(Texture* value) {
            setPointer(defaultValue, value);
            if (!this->value)
                setPointer(this->value, defaultValue);
        }

        __declspec(property(get = getDefaultValue, put = setDefaultValue)) Texture* DefaultValue;
    };
}