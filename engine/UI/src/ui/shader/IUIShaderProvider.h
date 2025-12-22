#pragma once

#include "engine/graphics/shader/IShader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class IUIShaderProvider:public Noncopyable {
    public:
        virtual IShader* loadInvalid() const = 0;

        virtual IShader* loadControl() const = 0;

        virtual IShader* loadText() const = 0;

        virtual IShader* loadShadow() const = 0;
    };
}