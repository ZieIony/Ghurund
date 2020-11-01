#pragma once

#include "ui/drawable/Drawable.h"
#include "core/string/String.h"

namespace Ghurund::UI {
    class GdiImage:public Drawable {
    private:
        unsigned int tint = 0;
 
    public:
        Gdiplus::Image* image;

        GdiImage(const String& fileName) {
            image = new Gdiplus::Image(UnicodeString(fileName).getData());
            size = { (float)image->GetWidth(), (float)image->GetHeight() };
        }

        GdiImage(Gdiplus::Image* image) {
            this->image = image;
            size = { (float)image->GetWidth(), (float)image->GetHeight() };
        }

        ~GdiImage() {
            delete image;
        }

        inline unsigned int getTint() const {
            return tint;
        }

        inline void setTint(unsigned int tint) {
            this->tint = tint;
        }

        __declspec(property(get = getTint, put = setTint)) unsigned int Tint;

        virtual void onDraw(Canvas& canvas);
    };

    typedef ScopedPointer<GdiImage> ImagePtr;
}