#include "RadioButton.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    RadioButton::RadioButton(CheckBoxRadioLayout* layout):Widget(layout) {
        Layout.SelectableView->OnClicked.add([this](Control&, const MouseClickedEventArgs&) {
            Layout.SelectableView->Selected = true;
            onCheckedChanged();
            return true;
        });
    }
}