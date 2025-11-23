#pragma once

#include "core/object/Noncopyable.h"
#include "engine/graphics/material/IMaterial.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;

    class IUIMaterialProvider:public Noncopyable {
    public:
        virtual IMaterial* makeInvalid() = 0;

        virtual IMaterial* makeControl() = 0;

        virtual IMaterial* makeText() = 0;

        virtual IMaterial* makeShadow() = 0;
    };
}