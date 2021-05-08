#pragma once

#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/image/Bitmap.h"

#include "reflection_897fba2b_a23c_460d_83e4_21c3247f53cc.h"

namespace Ghurund::UI {
    class BitmapDrawable:public ImageDrawable {
        reflection_897fba2b_a23c_460d_83e4_21c3247f53cc

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