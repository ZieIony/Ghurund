#pragma once

#include "SvgDocument.h"
#include "ui/Canvas.h"
#include "ui/drawable/ImageDrawable.h"

#include "reflection_ffc4b987_f4e4_4547_a9d1_7793f5bf7bae.h"

#include "reflection_aaa31ff7_a95b_448b_bd25_d3980f8a5458.h"

#include "reflection_ae6220df_a63e_4f87_8662_d4b6bc82788c.h"

namespace Ghurund::UI {
    class SvgDrawable:public ImageDrawable {
        reflection_ae6220df_a63e_4f87_8662_d4b6bc82788c

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