#include "ghuipch.h"
#include "ColorView.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"
#include <ui/Binding.h>

namespace Ghurund::UI {
    const Ghurund::Core::Type& ColorView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ColorView>();
        static auto PROPERTY_COLOR = Property<ColorView, const ColorAttr&>("Color", (const ColorAttr & (ColorView::*)()) & getColor, (void(ColorView::*)(const ColorAttr&)) & setColor);

        static const Ghurund::Core::Type TYPE = TypeBuilder<ColorView>(NAMESPACE_NAME, GH_STRINGIFY(ColorView))
            .withConstructor(CONSTRUCTOR)
            .withProperty(PROPERTY_COLOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ColorView::onDraw(ICanvas& canvas) {
        const Ghurund::UI::Color& c = color->getValue(*this);
        if (c.A > 0.0f) {
            canvas.Color = c;
            canvas.fillRect(0, 0, Size.Width, Size.Height);
        }
    }

    void ColorView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr) {
            AString colorAttrValue = colorAttr->Value();
            auto color = loader.loadColor(colorAttrValue.Data);
            if (color) {
                Color = *color;
                delete color;
            } else {
                auto text = std::format(_T("Invalid color value: '{}'.\n"), colorAttrValue);
                Logger::log(LogType::WARNING, text.c_str());
            }
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
