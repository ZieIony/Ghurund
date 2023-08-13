#pragma once

#include "core/resource/ResourcePath.h"
#include "ui/drawable/Drawable.h"

namespace Ghurund::UI {
    class DrawableFactory {
    public:
        virtual ~DrawableFactory() = 0 {}

        virtual Drawable* makeDrawable(const Ghurund::Core::ResourcePath& path) = 0;
    };
}