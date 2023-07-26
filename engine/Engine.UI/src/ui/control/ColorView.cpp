#include "ghuipch.h"
#include "ColorView.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/theme/Theme.h"
#include "ui/Canvas.h"
#include <ui/Binding.h>

namespace Ghurund::UI {
    const Ghurund::Core::Type& ColorView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ColorView>();
        static auto PROPERTY_COLOR = Property<ColorView, const ColorAttr&>("Color", &setColor);

        static const Ghurund::Core::Type TYPE = TypeBuilder<ColorView>(NAMESPACE_NAME, GH_STRINGIFY(ColorView))
            .withConstructor(CONSTRUCTOR)
            .withProperty(PROPERTY_COLOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ColorView::onThemeChanged() {
        const UI::Theme* theme = Theme;
        if (theme)
            color.resolve(*theme);
    }

    void ColorView::onDraw(ICanvas& canvas) {
        const Ghurund::UI::Color* c = color.get();
        if (c && c->A > 0.0f) {
            canvas.Color = *c;
            canvas.fillRect(0, 0, Size.Width, Size.Height);
        }
    }

    void ColorViewBackgroundStyle::apply(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_BACKGR0UND);
    }

    void ColorViewControlStyle::apply(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_CONTROL);
    }

    void ColorViewAccentStyle::apply(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_ACCENT);
    }
}
