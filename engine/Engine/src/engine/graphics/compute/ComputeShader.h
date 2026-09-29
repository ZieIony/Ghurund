#pragma once

#include "engine/graphics/shader/Shader.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ComputeShader:public Shader {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ComputeShader::GET_TYPE();
#pragma endregion
    };
}
