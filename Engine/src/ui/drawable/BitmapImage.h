#pragma once

#include "ui/gdi/Gdi.h"
#include "core/string/String.h"

namespace Ghurund::UI {
    class BitmapImage:public Pointer {
    private:
        IntSize size;

    public:
        Gdiplus::Image* image;

        BitmapImage(const String& fileName) {
            image = new Gdiplus::Image(UnicodeString(fileName).getData());
            size = { image->GetWidth(), image->GetHeight() };
        }

        BitmapImage(Gdiplus::Image* image) {
            this->image = image;
            size = { image->GetWidth(), image->GetHeight() };
        }

        ~BitmapImage() {
            delete image;
        }

        inline const IntSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) const IntSize& Size;
    };
}