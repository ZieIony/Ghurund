#pragma once

#include "core/resource/ResourcePath.h"
#include "ui/drawable/Drawable.h"

namespace Ghurund::UI {
    class IDrawableFactory:public Noncopyable {
    public:
        virtual Drawable* makeDrawable(const Ghurund::Core::ResourcePath& path) = 0;
    };
}