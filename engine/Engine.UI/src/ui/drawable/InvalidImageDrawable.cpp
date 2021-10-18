#include "ghuipch.h"
#include "InvalidImageDrawable.h"

#include "core/math/Rect.h"
#include "ui/Canvas.h"
#include "ui/image/Bitmap.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& InvalidImageDrawable::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<InvalidImageDrawable>(Ghurund::UI::NAMESPACE_NAME, "InvalidImageDrawable")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    InvalidImageDrawable::InvalidImageDrawable() {
        preferredSize = { 18, 18 };
    }

    void InvalidImageDrawable::onDraw(Canvas& canvas) {
        canvas.fillRect(0, 0, Size.width, Size.height, backgroundColor);
        canvas.drawRect(1, 1, Size.width - 2, Size.height - 2, borderColor, 2);
        canvas.drawLine(Size.width / 2 - 6, Size.height / 2 - 6, Size.width / 2 + 6, Size.height / 2 + 6, borderColor, 1.5);
        canvas.drawLine(Size.width / 2 - 6, Size.height / 2 + 6, Size.width / 2 + 6, Size.height / 2 - 6, borderColor, 1.5);
    }
}
