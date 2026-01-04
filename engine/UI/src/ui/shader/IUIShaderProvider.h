#pragma once

#include "engine/graphics/shader/Shader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class IUIShaderProvider:public Noncopyable {
    public:
        virtual Shader* loadInvalid() const = 0;

        virtual Shader* loadControl() const = 0;

        virtual Shader* loadText() const = 0;

        virtual Shader* loadShadow() const = 0;
    };
}