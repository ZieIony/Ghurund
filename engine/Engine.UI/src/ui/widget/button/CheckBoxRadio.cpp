#include "ghuipch.h"
#include "CheckBoxRadio.h"

#include "ui/control/ImageView.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    void CheckBoxRadioStyle::onStateChanged(Control& control) const {
        Widget<CheckBoxBinding>& checkBoxRadio = (Widget<CheckBoxBinding>&)control;
        CheckBoxBinding* layout = checkBoxRadio.Layout;
        if (!layout)
            return;
        if (!control.Enabled) {
            layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND));
        } else if (layout->Selectable->Pressed) {
            if (layout->Selectable->Selected) {
                //imageView->Image->Tint = theme->getColorAccentDark();
                layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
            } else {
                layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND));
            }
        } else if (layout->Selectable->Hovered || layout->Selectable->Focused) {
            if (layout->Selectable->Selected) {
                layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
            } else {
                layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND));
            }
        } else {
            if (layout->Selectable->Selected) {
                layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
            } else {
                layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND));
            }
        }
    }
    
}
