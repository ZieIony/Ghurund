#include "ghuipch.h"
#include "InvalidImageDrawable.h"

#include "core/math/Rect.h"
#include "ui/Canvas.h"
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

    void InvalidImageDrawable::onDraw(ICanvas& canvas, const Ghurund::Core::FloatSize& size) const {
        canvas.Color = backgroundColor;
        canvas.fillRect(0, 0, size.Width, size.Height);
        canvas.drawRect(1, 1, size.Width - 2, size.Height - 2, 2);
        canvas.drawLine(size.Width / 2 - 6, size.Height / 2 - 6, size.Width / 2 + 6, size.Height / 2 + 6, 1.5);
        canvas.drawLine(size.Width / 2 - 6, size.Height / 2 + 6, size.Width / 2 + 6, size.Height / 2 - 6, 1.5);
    }
}
