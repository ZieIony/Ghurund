#include "ghuipch.h"
#include "ToolbarAdapter.h"

#include "ui/style/Theme.h"

namespace Ghurund::UI {
    Control* ButtonToolbarAdapter::makeControl() const {
        return nullptr;// ghnew ImageButton(ghnew ImageButtonFlatLayout());
    }
    
    void ButtonToolbarAdapter::bind(Control& control, MenuItem*& item, size_t position) const {
        /*ImageButton& imageButton = (ImageButton&)control;
        ButtonMenuItem* menuItem = (ButtonMenuItem*)item;
        //imageButton.Name = menuItem->Text;
        imageButton.Image = makeShared<BitmapDrawable>(menuItem->Image);
        imageButton.Clicked.clear();
        imageButton.Clicked.add([menuItem](Control& sender, const MouseClickedEventArgs& args) {
            menuItem->ClickEventHandler(sender);
            return true;
        });*/
    }
    
    SeparatorToolbarAdapter::SeparatorToolbarAdapter(Theme& theme):theme(theme) {}

    Control* SeparatorToolbarAdapter::makeControl() const {
        Separator* separator = ghnew Separator();
        auto s = StyleRef(Theme::STYLE_SEPARATOR_HORIZONTAL);
        separator->Style = &s;
        //separator->PreferredSize.height = PreferredSize::Height::FILL;
        return separator;
    }
}
