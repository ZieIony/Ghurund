#include "ToolbarAdapter.h"
#include "ui/Theme.h"
#include "ui/drawable/BitmapImageDrawable.h"

namespace Ghurund::UI {
    Control* ButtonToolbarAdapter::makeControl() const {
        return ghnew ImageButton(ghnew ImageButtonFlatLayout());
    }
    
    void ButtonToolbarAdapter::bind(Control& control, MenuItem* const& item, size_t position) const {
        ImageButton& imageButton = (ImageButton&)control;
        ButtonMenuItem* menuItem = (ButtonMenuItem*)item;
        imageButton.Name = menuItem->Text;
        imageButton.Image = makeShared<BitmapImageDrawable>(menuItem->Image);
        imageButton.OnClicked.clear();
        imageButton.OnClicked.add([menuItem](Control& sender, const MouseClickedEventArgs& args) {
            menuItem->ClickEventHandler(sender);
            return true;
        });
    }
    
    SeparatorToolbarAdapter::SeparatorToolbarAdapter(Theme& theme):theme(theme) {}

    Control* SeparatorToolbarAdapter::makeControl() const {
        Separator* separator = ghnew Separator(theme.separatorStyle);
        separator->PreferredSize.height = PreferredSize::Height::FILL;
        return separator;
    }
}
