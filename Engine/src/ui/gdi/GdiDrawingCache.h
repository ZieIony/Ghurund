#pragma once

#include "GdiCanvas.h"
#include "ui/DrawingCache.h"

namespace Ghurund::UI {
    class GdiDrawingCache:public DrawingCache {
    private:
        GdiImage* image;

    public:
        GdiDrawingCache(Gdiplus::Bitmap* bitmap) {
            image = ghnew GdiImage(bitmap);
        }

        ~GdiDrawingCache() {
            image->release();
        }

        virtual void draw(Canvas& canvas) const override {
            image->draw(canvas);
        }
    };
}