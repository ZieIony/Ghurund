#include "CheckBox.h"

#include "ui/control/ImageView.h"
#include "ui/drawable/BitmapImageDrawable.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Type& CheckBox::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<CheckBox>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void CheckBox::onLayoutChanged() {
        __super::onLayoutChanged();
        if (Layout) {
            Layout->Selectable->Clicked.add([this](Control&, const MouseClickedEventArgs&) {
                Checked = !Checked;
                CheckedChanged();
                return true;
            });
            Layout->Selectable->StateChanged.add(stateHandler);
        }
    }
    
    void CheckBoxStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        CheckBox& checkBoxRadio = (CheckBox&)control;
        CheckBoxBinding* layout = checkBoxRadio.Layout;
        if (layout->Selectable->Selected) {
            layout->Image->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_CHECKBOX_CHECKED]);
        } else {
            layout->Image->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_CHECKBOX_UNCHECKED]);
        }
        __super::onStateChanged(control);
    }
}