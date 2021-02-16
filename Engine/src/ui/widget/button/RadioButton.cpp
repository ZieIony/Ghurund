#include "RadioButton.h"

#include "ui/control/ImageView.h"
#include "ui/drawable/BitmapImageDrawable.h"
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
        }
    }

    void RadioButtonStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        CheckBoxRadio& checkBoxRadio = (CheckBoxRadio&)control;
        CheckBoxLayout* layout = checkBoxRadio.Layout;
        if (layout->Selectable->Selected) {
            layout->Image->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_RADIOBUTTON_CHECKED]);
        } else {
            layout->Image->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_RADIOBUTTON_UNCHECKED]);
        }
        __super::onStateChanged(control);
    }
}