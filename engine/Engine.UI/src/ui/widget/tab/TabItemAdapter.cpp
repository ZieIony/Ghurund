#include "ghuipch.h"
#include "TabContainer.h"

#include "TextTabLayout.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    Tab* TabItemAdapter::makeControl() const {
        return nullptr;// ghnew Tab(ghnew TextTabLayout(theme));
    }

    void TabItemAdapter::bind(Tab& tabView, TabItem* const& tab, size_t position) const {
        //tabView.Layout->SelectableView->Selected = tabLayout.SelectedPosition == position;
        tabView.Layout->SelectableView->Clicked.add([this, position](Control& sender, const MouseClickedEventArgs& args) {
            //tabLayout.SelectedPosition = position;
            return true;
        });
    }

    void TextTabItemAdapter::bind(Tab& tabView, TabItem* const& tab, size_t position) const {
        __super::bind(tabView, tab, position);
        TextTabItem* textTab = (TextTabItem*)tab;
        //((TextTabLayout*)tabView.Layout)->TextBlock->Text = textTab->text;
    }
}