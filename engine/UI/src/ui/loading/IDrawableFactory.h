#pragma once

#include "core/resource/ResourcePath.h"
#include "ui/drawable/Drawable.h"

namespace Ghurund::UI {
    class IDrawableFactory {
    public:
        virtual ~IDrawableFactory() = 0 {}

        virtual Drawable* makeDrawable(const Ghurund::Core::ResourcePath& path) = 0;
    };
}