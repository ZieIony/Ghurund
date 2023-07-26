#include "ghuipch.h"
#include "RadioButton.h"

#include "ui/control/DrawableView.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    void RadioButton::onLayoutChanged() {
        __super::onLayoutChanged();
        clickable->clicked += [this](Control&, const MouseClickedEventArgs&) {
            Checked = checked;
            return true;
            };
        clickable->stateChanged += stateHandler;
    }

    const Ghurund::Core::Type& RadioButton::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<RadioButton>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<RadioButton>(NAMESPACE_NAME, GH_STRINGIFY(RadioButton))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void RadioButtonStyle::onStateChanged(Control& control) const {
        const Theme* theme = control.Theme;
        if (!theme)
            return;
        /*RadioButton& checkBoxRadio = (RadioButton&)control;
        CheckBoxBinding* layout = checkBoxRadio.Layout;
        if (layout->Selectable->Selected) {
            SharedPointer<ImageDrawable> drawable = (ImageDrawable*)theme->Drawables[Theme::IMAGE_RADIOBUTTON_CHECKED]->clone();
            layout->Image->Image = drawable;
        } else {
            SharedPointer<ImageDrawable> drawable = (ImageDrawable*)theme->Drawables[Theme::IMAGE_RADIOBUTTON_UNCHECKED]->clone();
            layout->Image->Image = drawable;
        }*/
        /*CheckBoxRadio& checkBoxRadio = (CheckBoxRadio&)control;
            return;
        if (!control.Enabled) {
            layout->Image->Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND));
        } else if (layout->Selectable->Pressed) {
            if (layout->Selectable->Selected) {
                //drawableView->Image->Tint = theme->getColorAccentDark();
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
        }*/
    }
}