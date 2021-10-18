#include "ghuipch.h"
#include "CheckBox.h"

#include "ui/control/ImageView.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& CheckBox::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<CheckBox>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBox>(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void CheckBox::onLayoutChanged() {
        __super::onLayoutChanged();
        if (Layout && Layout->Selectable) {
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
        if (layout) {
            if (layout->Selectable->Selected) {
                SharedPointer<ImageDrawable> image = clone(theme->Images[Theme::IMAGE_CHECKBOX_CHECKED]);
                layout->Image->Image = image;
            } else {
                SharedPointer<ImageDrawable> image = clone(theme->Images[Theme::IMAGE_CHECKBOX_UNCHECKED]);
                layout->Image->Image = image;
            }
        }
        __super::onStateChanged(control);
    }
}