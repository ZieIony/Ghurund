#pragma once

#include "core/Pointer.h"
#include "core/string/String.h"

#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>

namespace Ghurund::UI {
    class GdiImage:public Pointer {
    public:
        Gdiplus::Image* image;

        GdiImage(const String& fileName) {
            image = new Gdiplus::Image(UnicodeString(fileName).getData());
        }

        GdiImage(Gdiplus::Image* image) {
            this->image = image;
        }

        ~GdiImage() {
            delete image;
        }

        inline unsigned int getWidth() const {
            return image->GetWidth();
        }

        __declspec(property(get = getWidth)) unsigned int Width;

        inline unsigned int getHeight() const {
            return image->GetHeight();
        }

        __declspec(property(get = getHeight)) unsigned int Height;
    };
}