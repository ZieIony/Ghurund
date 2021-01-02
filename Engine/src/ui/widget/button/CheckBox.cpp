#include "CheckBox.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    CheckBox::CheckBox(CheckBoxRadioLayout* layout):Widget(layout) {
        Focusable = true;
        Layout.SelectableView->OnStateChanged.add(OnStateChanged);
        Layout.SelectableView->OnClicked.add([this](Control&, const MouseClickedEventArgs&) {
            Checked = !Checked;
            onCheckedChanged();
            return true;
        });
    }

}