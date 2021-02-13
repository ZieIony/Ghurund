#include "ColorView.h"

#include "ui/LayoutLoader.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
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
