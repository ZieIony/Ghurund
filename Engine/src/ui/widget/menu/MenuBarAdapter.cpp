#include "MenuBarAdapter.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    ButtonMenuBarAdapter::ButtonMenuBarAdapter(Theme& theme):theme(theme) {}
    
    Control* ButtonMenuBarAdapter::makeControl() const {
        return ghnew TextButton(ghnew TextButtonFlatLayout(theme));
    }
    
    void ButtonMenuBarAdapter::bind(Control& control, MenuItem* const& item, size_t position) const {
        TextButton& textButton = (TextButton&)control;
        ButtonMenuItem* menuItem = (ButtonMenuItem*)item;
        TextButtonLayout& layout = (TextButtonLayout&)textButton.Layout;
        layout.TextBlock->Text = menuItem->Text;
        textButton.OnClicked.clear();
        textButton.OnClicked.add([menuItem](Control& sender, const MouseButton& args) {
            menuItem->ClickEventHandler(sender);
            return true;
        });
    }
}

