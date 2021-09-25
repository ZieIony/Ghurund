#include "ghuipch.h"
#include "BitmapDrawable.h"

#include "core/math/Rect.h"
#include "ui/Canvas.h"
#include "ui/image/Bitmap.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& BitmapDrawable::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<BitmapDrawable>(Ghurund::UI::NAMESPACE_NAME, "BitmapDrawable")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    BitmapDrawable::BitmapDrawable(Bitmap* image) {
        this->image = image;
        image->addReference();
        preferredSize = { (float)image->Size.width, (float)image->Size.height };
    }

    BitmapDrawable::~BitmapDrawable() {
        image->release();
    }

    void BitmapDrawable::onDraw(Canvas& canvas) {
        auto dst = FloatRect{ 0, 0, size.width, size.height };
        if (Tint) {
            canvas.drawImage(image->Data, dst, Tint, Alpha);
        } else {
            canvas.drawImage(image->Data, dst, Alpha);
        }
    }
}
