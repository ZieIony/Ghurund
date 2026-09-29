#pragma once

#include "engine/graphics/shader/Shader.h"

namespace Ghurund::Engine {
    class GraphicsShader:public Shader {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GraphicsShader::GET_TYPE();
#pragma endregion

    protected:
        bool isTransparencyEnabled = false;

    public:
        bool getIsTransparencyEnabled() {
            return isTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;
    };
}
