#include "RadioButton.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void RadioButton::onLayoutChanged() {
        __super::onLayoutChanged();
        if (Layout) {
            Layout->SelectableView->StateChanged.add(StateChanged);
            Layout->SelectableView->OnClicked.add([this](Control&, const MouseClickedEventArgs&) {
                Layout->SelectableView->Selected = true;
                onCheckedChanged();
                return true;
            });
        }
    }
}