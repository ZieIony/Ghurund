#pragma once

#include "ui/drawable/Drawable.h"

namespace Ghurund::UI {
    class DrawableFactory {
    public:
        virtual ~DrawableFactory() = 0 {}

        virtual Drawable* makeDrawable(const FilePath& path) = 0;
    };
}