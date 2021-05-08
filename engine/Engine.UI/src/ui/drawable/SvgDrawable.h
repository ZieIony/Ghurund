#pragma once

#include "SvgDocument.h"
#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"

#include "reflection_ffc4b987_f4e4_4547_a9d1_7793f5bf7bae.h"

namespace Ghurund::UI {
    class SvgDrawable:public ImageDrawable {
        reflection_ffc4b987_f4e4_4547_a9d1_7793f5bf7bae

    private:
        SvgDocument* image;

    public:
        SvgDrawable(SvgDocument* image) {
            this->image = image;
            image->addReference();
            preferredSize = { image->Size.width, image->Size.height };
        }

        virtual void onDraw(Canvas& canvas) override {
            auto dst = D2D1::RectF(0, 0, size.width, size.height);
            canvas.drawImage(*image->Data);
        }

        virtual SvgDrawable* clone() override {
            return ghnew SvgDrawable(image);
        }
    };
}