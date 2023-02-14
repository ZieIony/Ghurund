#include "ghuipch.h"
#include "Border.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Border::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Border>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Border>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(Border))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Border::onDraw(ICanvas& canvas) {
        uint32_t color = Color.getValue(*this);
        if (!color || Thickness < 0.1f)
            return;
        canvas.Color = color;
        if (shape) {
            canvas.drawShape(*shape, thickness);
        } else {
            canvas.drawRect(Position.x + Thickness / 2, Position.y + Thickness / 2, Size.Width - Thickness, Size.Height - Thickness, thickness);
        }
    }
    
    void BorderOnBackgroundStyle::onStateChanged(Border& control) const {
        if (control.Enabled) {
            control.Color = ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND);
        } else {
            control.Color = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        }
    }
    
    void BorderAccentStyle::onStateChanged(Border& control) const {
        if (control.Enabled) {
            control.Color = ColorRef(Theme::COLOR_ACCENT);
        } else {
            control.Color = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        }
    }
}
