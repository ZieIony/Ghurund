#include "CheckBox.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    CheckBox::CheckBox(CheckBoxRadioLayout* layout):Widget2(layout) {
        Layout.SelectableView->OnClicked.add([this](Control& sender, MouseButton button) {
            Checked = !Checked;
            return true;
        });
    }

}