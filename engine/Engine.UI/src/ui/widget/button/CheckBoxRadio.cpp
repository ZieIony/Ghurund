#include "ghuipch.h"
#include "CheckBoxRadio.h"

#include "ui/control/ImageView.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    void CheckBoxRadioStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        Widget<CheckBoxBinding>& checkBoxRadio = (Widget<CheckBoxBinding>&)control;
        CheckBoxBinding* layout = checkBoxRadio.Layout;
        if (!layout)
            return;
        if (!layout->Image->Image)
            return;
        if (!control.Enabled) {
            layout->Image->Image->Tint = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        } else if (layout->Selectable->Pressed) {
            if (layout->Selectable->Selected) {
                //imageView->Image->Tint = theme->getColorAccentDark();
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
            }
        } else if (layout->Selectable->Hovered || layout->Selectable->Focused) {
            if (layout->Selectable->Selected) {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_SECONDARY_ONBACKGROUND];
            }
        } else {
            if (layout->Selectable->Selected) {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_SECONDARY_ONBACKGROUND];
            }
        }
    }
    
}
