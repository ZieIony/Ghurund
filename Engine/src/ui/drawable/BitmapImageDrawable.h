#pragma once

#include "BitmapImage.h"
#include "Drawable.h"

namespace Ghurund::UI {
    class BitmapImageDrawable:public ImageDrawable {
    private:
        BitmapImage* image;

    public:
        BitmapImageDrawable(BitmapImage* image) {
            this->image = image;
            image->addReference();
            preferredSize = { (float)image->Size.width, (float)image->Size.height };
        }

        ~BitmapImageDrawable() {
            image->release();
        }

        virtual void onDraw(Canvas& canvas) override {
            auto dst = D2D1::RectF(position.x, position.y, position.x + size.width, position.y + size.height);
            if (Tint) {
                canvas.drawImage(*image, dst, Tint);
            } else {
                canvas.drawImage(*image, dst);
            }
        }
    };
}