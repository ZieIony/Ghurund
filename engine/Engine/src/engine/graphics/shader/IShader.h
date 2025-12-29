#pragma once

#include "TextureInput.h"
#include "ValueInput.h"

#include "core/resource/Resource.h"
#include "engine/parameter/Parameter.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class IShader:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = IShader::GET_TYPE();
#pragma endregion

    protected:
        bool isTransparencyEnabled = false;
        List<ValueInput> valueInputs;
        List<TextureInput> textureInputs;

    public:
        bool getIsTransparencyEnabled() {
            return isTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

        inline const List<ValueInput>& getValueInputs() const {
            return valueInputs;
        }

        __declspec(property(get = getValueInputs)) const List<ValueInput>& ValueInputs;

        inline const List<TextureInput>& getTextureInputs() const {
            return textureInputs;
        }

        __declspec(property(get = getTextureInputs)) const List<TextureInput>& TextureInputs;
    };
}