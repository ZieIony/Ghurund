#include "TabContainer.h"
#include "TextTab.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    Tab* TabItemAdapter::makeControl() const {
        ScopedPointer<TextTabStyle> style = ghnew TextTabStyle(theme);
        return ghnew Tab(style);
    }

    void TabItemAdapter::bind(Tab& tabView, TabItem* const& tab, size_t position) const {
        tabView.Layout.SelectableView->Selected = tabLayout.SelectedPosition == position;
        tabView.Layout.SelectableView->OnClicked.add([this, position](Control& sender, const MouseButton& args) {
            tabLayout.SelectedPosition = position;
            return true;
        });
    }

    void TextTabItemAdapter::bind(Tab& tabView, TabItem* const& tab, size_t position) const {
        __super::bind(tabView, tab, position);
        TextTabItem* textTab = (TextTabItem*)tab;
        ((TextTabLayout&)tabView.Layout).TextBlock->Text = textTab->text;
    }
}