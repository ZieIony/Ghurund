#pragma once

#include "TextureConstant.h"
#include "ValueConstant.h"
#include "BufferConstant.h"

#include "core/resource/Resource.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class Shader:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Shader::GET_TYPE();
#pragma endregion

    protected:
        bool isTransparencyEnabled = false;
        List<ValueConstant> valueConstants;
        List<BufferConstant> bufferConstants;
        List<TextureConstant> textureConstants;

    public:
        bool getIsTransparencyEnabled() {
            return isTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

        inline const List<ValueConstant>& getValueConstants() const {
            return valueConstants;
        }

        __declspec(property(get = getValueConstants)) const List<ValueConstant>& ValueConstants;

        inline const List<BufferConstant>& getBufferInputs() const {
            return bufferConstants;
        }

        __declspec(property(get = getBufferInputs)) const List<BufferConstant>& BufferConstants;

        inline const List<TextureConstant>& getTextureConstants() const {
            return textureConstants;
        }

        __declspec(property(get = getTextureConstants)) const List<TextureConstant>& TextureConstants;
    };
}