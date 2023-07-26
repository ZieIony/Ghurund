#include "ghuipch.h"
#include "Border.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/theme/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Border::GET_TYPE() {
        static auto PROPERTY_SHAPE = Property<Border, std::unique_ptr<Ghurund::UI::Shape>&>("Shape", &setShape);

        static const auto CONSTRUCTOR = Constructor<Border>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Border>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(Border))
            .withProperty(PROPERTY_SHAPE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Border::onThemeChanged() {
        const UI::Theme* theme = Theme;
        if (theme)
            color.resolve(*theme);
    }

    void Border::onDraw(ICanvas& canvas) {
        const UI::Color* color = this->color.get();
        if (!color || thickness < 0.1f)
            return;
        canvas.Color = *color;
        if (shape) {
            canvas.drawShape(*shape, thickness);
        } else {
            canvas.drawRect(Position.x + thickness / 2, Position.y + thickness / 2, Size.Width - thickness, Size.Height - thickness, thickness);
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
