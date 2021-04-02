#include "ghuipch.h"
#include "RadioButton.h"

#include "ui/control/ImageView.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Type& RadioButton::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<RadioButton>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(RadioButton))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void RadioButton::onLayoutChanged() {
        __super::onLayoutChanged();
        if (Layout) {
            Layout->Selectable->Clicked.add([this](Control&, const MouseClickedEventArgs&) {
                Checked = true;
                CheckedChanged();
                return true;
            });
            Layout->Selectable->StateChanged.add(stateHandler);
        }
    }

    void RadioButtonStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        RadioButton& checkBoxRadio = (RadioButton&)control;
        CheckBoxBinding* layout = checkBoxRadio.Layout;
        if (layout->Selectable->Selected) {
            layout->Image->Image = (ImageDrawable*)theme->Images[Theme::IMAGE_RADIOBUTTON_CHECKED]->clone();
        } else {
            layout->Image->Image = (ImageDrawable*)theme->Images[Theme::IMAGE_RADIOBUTTON_UNCHECKED]->clone();
        }
        layout->Image->Image->release();
        __super::onStateChanged(control);
    }
}