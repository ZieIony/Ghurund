#include "RadioButton.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    RadioButton::RadioButton(CheckBoxRadioLayout* layout):Widget2(layout) {
        Layout.SelectableView->OnClicked.add([this](Control& sender, MouseButton button) {
            Layout.SelectableView->Selected = true;
            onCheckedChanged();
            return true;
        });
    }
}