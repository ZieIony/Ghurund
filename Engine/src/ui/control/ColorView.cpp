#include "ghpch.h"
#include "ColorView.h"

#include "ui/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Type& ColorView::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ColorView>();
        static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ColorView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ColorView::onDraw(Canvas& canvas) {
        canvas.fillRect(0, 0, Size.width, Size.height, color);
    }

    Status ColorView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr)
            Color = loader.loadColor(colorAttr->Value());
        return Status::OK;
    }

    void ColorViewBackgroundStyle::onThemeChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        ((ColorView&)control).Color = theme->Colors[Theme::COLOR_BACKGR0UND];
    }

    void ColorViewControlStyle::onThemeChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        ((ColorView&)control).Color = theme->Colors[Theme::COLOR_CONTROL];
    }

    void ColorViewAccentStyle::onThemeChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        ((ColorView&)control).Color = theme->Colors[Theme::COLOR_ACCENT];
    }
}
