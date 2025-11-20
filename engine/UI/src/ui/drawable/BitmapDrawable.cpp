#include "ghuipch.h"
#include "BitmapDrawable.h"

#include "core/math/Rect.h"
#include "core/image/Image.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& BitmapDrawable::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<BitmapDrawable>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    BitmapDrawable::BitmapDrawable(Image* image) {
        this->image = image;
        image->addReference();
        preferredSize = { (float)image->Size.Width, (float)image->Size.Height };
    }

    BitmapDrawable::~BitmapDrawable() {
        image->release();
    }

    void BitmapDrawable::draw(RenderGroup& group, const FloatSize& size, const Ghurund::UI::Color& tint) const {
        auto dst = FloatRect{ 0, 0, size.Width, size.Height };
        /*if (tint.A) {
            canvas.drawImage(*image, dst, tint, tint.A);
        } else {
            canvas.drawImage(*image, dst);
        }*/
    }
}
