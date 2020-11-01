#include "CheckBox.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    CheckBox::CheckBox(CheckBoxRadioLayout* layout):Widget2(layout) {
        Focusable = true;
        Layout.SelectableView->OnClicked.add([this](Control& sender, MouseButton button) {
            Checked = !Checked;
            onCheckedChanged();
            return true;
        });
    }

}