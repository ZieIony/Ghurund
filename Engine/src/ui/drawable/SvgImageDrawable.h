#pragma once

#include "SvgImage.h"
#include "Drawable.h"

namespace Ghurund::UI {
    class SvgImageDrawable:public ImageDrawable {
    private:
        SvgImage* image;

    public:
        SvgImageDrawable(SvgImage* image) {
            this->image = image;
            image->addReference();
            preferredSize = { image->Size.width, image->Size.height };
        }

        virtual void onDraw(Canvas& canvas) override {
            auto dst = D2D1::RectF(position.x, position.y, position.x + size.width, position.y + size.height);
            canvas.drawImage(*image);
        }
    };
}