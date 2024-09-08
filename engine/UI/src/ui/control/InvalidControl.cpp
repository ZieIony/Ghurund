#include "ghuipch.h"
#include "InvalidControl.h"

#include "ui/Canvas.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& InvalidControl::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<InvalidControl>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<InvalidControl>(NAMESPACE_NAME, GH_STRINGIFY(InvalidControl))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void InvalidControl::onDraw(ICanvas& canvas) {
        canvas.Color = backgroundColor;
        canvas.fillRect(0, 0, Size.Width, Size.Height);
        canvas.Color = borderColor;
        canvas.drawRect(1, 1, Size.Width - 2, Size.Height - 2, 2, strokeStyle.get());
    }
}