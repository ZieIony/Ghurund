#pragma once

#include "Parameter.h"
#include "engine/graphics/ITexture.h"

namespace Ghurund::Engine {
    class TextureParameter:public Parameter {
    private:
        ITexture* value;
        ITexture* defaultValue = nullptr;

    public:
        TextureParameter(const AString& constantName):Parameter(constantName, ParameterType::TEXTURE) {
            value = nullptr;
            empty = true;
        }

        TextureParameter(const AString& constantName, ITexture* value):Parameter(constantName, ParameterType::TEXTURE) {
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

        inline ITexture* getValue() {
            return value;
        }

        void setValue(ITexture* value) {
            setPointer(this->value, value);
            empty = false;
        }

        void clearValue() {
            setPointer(value, defaultValue);
            empty = true;
        }

        __declspec(property(get = getValue, put = setValue)) ITexture* Value;

        inline ITexture* getDefaultValue() const {
            return defaultValue;
        }

        void setDefaultValue(ITexture* value) {
            setPointer(defaultValue, value);
            if (!this->value)
                setPointer(this->value, defaultValue);
        }

        __declspec(property(get = getDefaultValue, put = setDefaultValue)) ITexture* DefaultValue;
    };
}