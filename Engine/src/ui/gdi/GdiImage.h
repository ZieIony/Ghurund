#pragma once

#include "ui/drawable/Drawable.h"
#include "core/string/String.h"

#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>

namespace Ghurund::UI {
    class GdiImage:public Drawable {
    public:
        Gdiplus::Image* image;

        GdiImage(const String& fileName) {
            image = new Gdiplus::Image(UnicodeString(fileName).getData());
            size = { image->GetWidth(), image->GetHeight() };
        }

        GdiImage(Gdiplus::Image* image) {
            this->image = image;
            size = { image->GetWidth(), image->GetHeight() };
        }

        ~GdiImage() {
            delete image;
        }

        virtual void draw(Canvas& canvas) const;
    };

    typedef ScopedPointer<GdiImage> ImagePtr;
}