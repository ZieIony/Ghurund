#include "ghuipch.h"
#include "ColorView.h"

#include "ui/layout/LayoutLoader.h"
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

    void ColorView::onDraw(Canvas& canvas) {
        canvas.fillRect(0, 0, Size.width, Size.height, color->getValue(*this));
    }

    Status ColorView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr) {
            auto color = loader.loadColor(colorAttr->Value());
            Color = *color;
            delete color;
        }
        return Status::OK;
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
