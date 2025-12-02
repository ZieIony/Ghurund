#pragma once

#include "Parameter.h"
#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine {
    class TextureParameter:public Parameter {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<TextureParameter>()
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = TextureParameter::GET_TYPE();
#pragma endregion

    private:
        ITexture* value;

    public:
        TextureParameter(const AString& constantName):Parameter(constantName), value(nullptr) {}

        TextureParameter(const AString& constantName, ITexture* value):Parameter(constantName), value(value) {
            value->addReference();
            isEmpty = false;
        }

        ~TextureParameter() {
            if (value)
                value->release();
        }

        inline ITexture* getValue() {
            return value;
        }

        void setValue(ITexture* value) {
            setPointer(this->value, value);
            isEmpty = false;
        }

        void clearValue() {
            if (value) {
                value->release();
                value = nullptr;
            }
            isEmpty = true;
        }

        __declspec(property(get = getValue, put = setValue)) ITexture* Value;

        virtual size_t getSize() const override {
            // TODO: this class shouldn't have this method
            throw NotSupportedException();
        }
    };
}