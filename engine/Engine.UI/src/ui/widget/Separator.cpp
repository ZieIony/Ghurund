#include "ghuipch.h"
#include "SeparatorStyle.h"

#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Separator::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Separator>(NAMESPACE_NAME, GH_STRINGIFY(Separator))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Separator::Separator() {
        colorView = ghnew ColorView();
        Child = colorView;
    }

    void SeparatorStyle::onStateChanged(Control& control) const {
        if (control.Enabled) {
            ((Separator&)control).Color = ColorRef(Theme::COLOR_CONTROL);
        } else {
            ((Separator&)control).Color = ColorRef(Theme::COLOR_BACKGR0UND);
        }
    }

    void SeparatorStyle::onThemeChanged(Control& control) const {
        ((Separator&)control).Thickness = 1;
    }

    void SeparatorHorizontalStyle::onThemeChanged(Control& control) const {
        __super::onThemeChanged(control);
        ((Separator&)control).Padding.Vertical = 4;
        ((Separator&)control).Padding.Horizontal = 0;
    }

    void SeparatorVerticalStyle::onThemeChanged(Control& control) const {
        __super::onThemeChanged(control);
        ((Separator&)control).Padding.Vertical = 0;
        ((Separator&)control).Padding.Horizontal = 4;
    }
}