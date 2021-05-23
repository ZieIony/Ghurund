#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/image/Bitmap.h"

#include "reflection_6cfe1e10_6ed4_4830_b2be_97752c7b6470.h"

namespace Ghurund::UI {
    class BitmapDrawable:public ImageDrawable {
        reflection_6cfe1e10_6ed4_4830_b2be_97752c7b6470

    private:
        Bitmap* image;

    public:
        BitmapDrawable(Bitmap* image);

        ~BitmapDrawable();

        virtual void onDraw(Canvas& canvas) override;

        virtual BitmapDrawable* clone() override {
            return ghnew BitmapDrawable(image);
        }
    };
}