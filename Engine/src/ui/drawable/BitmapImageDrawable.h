#pragma once

#include "Drawable.h"

namespace Ghurund::UI {
    class BitmapImage;

    class BitmapImageDrawable:public ImageDrawable {
    private:
        BitmapImage* image;

    public:
        BitmapImageDrawable(BitmapImage* image);

        ~BitmapImageDrawable();

        virtual void onDraw(Canvas& canvas) override;
    };
}