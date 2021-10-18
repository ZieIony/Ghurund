#include "ghuipch.h"
#include "InvalidControl.h"

#include "ui/Canvas.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& InvalidControl::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<InvalidControl>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<InvalidControl>(NAMESPACE_NAME, GH_STRINGIFY(InvalidControl))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void InvalidControl::onDraw(Canvas& canvas) {
        canvas.fillRect(0, 0, Size.width, Size.height, backgroundColor);
        canvas.drawRect(1, 1, Size.width - 2, Size.height - 2, borderColor, 2, &strokeStyle);
    }
}