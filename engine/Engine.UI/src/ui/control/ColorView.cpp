#include "ghuipch.h"
#include "ColorView.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ColorView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ColorView>();
        static const Ghurund::Core::Type& TYPE = TypeBuilder<ColorView>(NAMESPACE_NAME, GH_STRINGIFY(ColorView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ColorView::onDraw(ICanvas& canvas) {
        canvas.fillRect(0, 0, Size.width, Size.height, color->getValue(*this));
    }

    void ColorView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr) {
            auto color = loader.loadColor(colorAttr->Value());
            Color = *color;
            delete color;
        }
    }

    void ColorViewBackgroundStyle::onThemeChanged(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_BACKGR0UND);
    }

    void ColorViewControlStyle::onThemeChanged(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_CONTROL);
    }

    void ColorViewAccentStyle::onThemeChanged(ColorView& control) const {
        control.Color = ColorRef(Theme::COLOR_ACCENT);
    }
}
