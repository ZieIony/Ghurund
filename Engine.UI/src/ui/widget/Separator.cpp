#include "ghuipch.h"
#include "SeparatorStyle.h"

#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Type& Separator::GET_TYPE() {
        static const Ghurund::Type TYPE = Ghurund::TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Separator))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Separator::Separator() {
        colorView = ghnew ColorView();
        Child = colorView;
    }

    void SeparatorStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        if (control.Enabled) {
            ((Separator&)control).Color = theme->Colors[Theme::COLOR_CONTROL];
        } else {
            ((Separator&)control).Color = theme->Colors[Theme::COLOR_BACKGR0UND];
        }
    }

    void SeparatorStyle::onThemeChanged(Control& control) const {
        ((Separator&)control).Thickness = 1;
    }

    void SeparatorHorizontalStyle::onThemeChanged(Control& control) const {
        __super::onThemeChanged(control);
        control.PreferredSize.width = PreferredSize::Width::FILL;
        control.PreferredSize.height = PreferredSize::Height::WRAP;
        ((Separator&)control).Padding.Vertical = 4;
        ((Separator&)control).Padding.Horizontal = 0;
    }

    void SeparatorVerticalStyle::onThemeChanged(Control& control) const {
        __super::onThemeChanged(control);
        control.PreferredSize.width = PreferredSize::Width::WRAP;
        control.PreferredSize.height = PreferredSize::Height::FILL;
        ((Separator&)control).Padding.Vertical = 0;
        ((Separator&)control).Padding.Horizontal = 4;
    }
}