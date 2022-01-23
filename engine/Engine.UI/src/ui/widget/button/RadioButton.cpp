#include "ghuipch.h"
#include "RadioButton.h"

#include "ui/control/ImageView.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& RadioButton::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<RadioButton>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<RadioButton>(NAMESPACE_NAME, GH_STRINGIFY(RadioButton))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void RadioButtonStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        /*RadioButton& checkBoxRadio = (RadioButton&)control;
        CheckBoxBinding* layout = checkBoxRadio.Layout;
        if (layout->Selectable->Selected) {
            SharedPointer<ImageDrawable> image = (ImageDrawable*)theme->Images[Theme::IMAGE_RADIOBUTTON_CHECKED]->clone();
            layout->Image->Image = image;
        } else {
            SharedPointer<ImageDrawable> image = (ImageDrawable*)theme->Images[Theme::IMAGE_RADIOBUTTON_UNCHECKED]->clone();
            layout->Image->Image = image;
        }*/
        __super::onStateChanged(control);
    }
}