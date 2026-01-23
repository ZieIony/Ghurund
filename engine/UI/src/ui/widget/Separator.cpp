#include "ghuipch.h"
#include "Separator.h"

#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Separator::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Separator>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Separator::Separator() {
        //colorView = ghnew ColorView();
        //Child = colorView;
    }

    void Separator::onStateChanged() {
        if (IsEnabled) {
            Color = Theme::COLOR_CONTROL;
        } else {
            Color = Theme::COLOR_BACKGR0UND;
        }
    }

    void Separator::onThemeChanged() {
        Thickness = 1;
        //Padding.Vertical = 4;
        //Padding.Horizontal = 0;
    }
}