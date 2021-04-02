#include "ghpch.h"
#include "BitmapImageDrawable.h"

#include "BitmapImage.h"
#include "core/math/Rect.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    BitmapImageDrawable::BitmapImageDrawable(BitmapImage* image) {
        this->image = image;
        image->addReference();
        preferredSize = { (float)image->Size.width, (float)image->Size.height };
    }

    BitmapImageDrawable::~BitmapImageDrawable() {
        image->release();
    }

    void BitmapImageDrawable::onDraw(Canvas& canvas) {
        auto dst = FloatRect{ 0, 0, size.width, size.height };
        if (Tint) {
            canvas.drawImage(image->Data, dst, Tint, Alpha);
        } else {
            canvas.drawImage(image->Data, dst, Alpha);
        }
    }
}
