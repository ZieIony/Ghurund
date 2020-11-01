#pragma once

#include "Drawable.h"

namespace Ghurund::UI {
    class VectorImage:public Drawable {
        unsigned int tint = 0;

        inline unsigned int getTint() const {
            return tint;
        }

        inline void setTint(unsigned int tint) {
            this->tint = tint;
        }

        __declspec(property(get = getTint, put = setTint)) unsigned int Tint;
    };

    typedef ScopedPointer<VectorImage> VectorImagePtr;
}