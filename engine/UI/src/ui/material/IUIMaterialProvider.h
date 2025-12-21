#pragma once

#include "core/object/Noncopyable.h"
#include "engine/graphics/material/Material.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;

    class IUMaterialProvider:public Noncopyable {
    public:
        virtual Material* makeInvalid() = 0;

        virtual Material* makeControl() = 0;

        virtual Material* makeText() = 0;

        virtual Material* makeShadow() = 0;
    };
}