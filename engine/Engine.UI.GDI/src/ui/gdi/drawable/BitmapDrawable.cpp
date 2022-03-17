#include "ghuigdipch.h"
#include "BitmapDrawable.h"

#include "core/math/Rect.h"
#include "ui/Canvas.h"
#include "ui/gdi/image/Bitmap.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI::GDI {
    const Ghurund::Core::Type& BitmapDrawable::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<BitmapDrawable>(Ghurund::UI::NAMESPACE_NAME, "BitmapDrawable")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    BitmapDrawable::BitmapDrawable(Bitmap* image) {
        this->image = image;
        image->addReference();
        preferredSize = { (float)image->Size.Width, (float)image->Size.Height };
    }

    BitmapDrawable::~BitmapDrawable() {
        image->release();
    }

    void BitmapDrawable::onDraw(ICanvas& canvas) {
        auto dst = FloatRect{ 0, 0, size.Width, size.Height };
        if (Tint) {
            canvas.drawImage(*image, dst, Tint, Alpha);
        } else {
            canvas.drawImage(*image, dst, Alpha);
        }
    }
}
