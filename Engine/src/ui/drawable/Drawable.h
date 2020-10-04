#pragma once

#include "core/Pointer.h"
#include "core/ScopedPointer.h"
#include "ui/Size.h"

namespace Ghurund::UI {
    class Canvas;

    class Drawable:public Pointer {
    protected:
        IntSize size;
        unsigned int tint = 0;

    public:
        inline IntSize& getSize() {
            return size;
        }

        inline void setSize(IntSize& size) {
            this->size = size;
        }

        __declspec(property(get = getSize, put = setSize)) IntSize Size;

        inline unsigned int getTint() const {
            return tint;
        }

        inline void setTint(unsigned int tint) {
            this->tint = tint;
        }

        __declspec(property(get = getTint, put = setTint)) unsigned int Tint;

        virtual void draw(Canvas& canvas) const = 0;
    };

    typedef ScopedPointer<Drawable> DrawablePtr;
}