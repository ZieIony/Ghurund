#include "ghuipch.h"
#include "CheckBox.h"

#include "ui/control/DrawableView.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& CheckBox::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<CheckBox>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBox>(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void CheckBoxStyle::onStateChanged(Control& control) const {
        const Theme* theme = control.Theme;
        if (!theme)
            return;
        /*CheckBox& checkBoxRadio = (CheckBox&)control;
            if (checkBoxRadio->selectable->Selected) {
                SharedPointer<ImageDrawable> drawable = (ImageDrawable*)theme->Drawables[Theme::IMAGE_CHECKBOX_CHECKED]->clone();
                checkBoxRadio->drawable->Image = drawable;
            } else {
                SharedPointer<ImageDrawable> drawable = (ImageDrawable*)theme->Drawables[Theme::IMAGE_CHECKBOX_UNCHECKED]->clone();
                checkBoxRadio->drawable->Image = drawable;
            }*/
        __super::onStateChanged(control);
    }
}