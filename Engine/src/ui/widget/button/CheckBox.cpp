#include "CheckBox.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void CheckBox::onLayoutChanged() {
        __super::onLayoutChanged();
        if (Layout) {
            Layout->SelectableView->StateChanged.add(StateChanged);
            Layout->SelectableView->OnClicked.add([this](Control&, const MouseClickedEventArgs&) {
                Checked = !Checked;
                onCheckedChanged();
                return true;
            });
        }
    }
}