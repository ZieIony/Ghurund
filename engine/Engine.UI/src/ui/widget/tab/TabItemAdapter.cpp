#include "ghuipch.h"
#include "TabContainer.h"

#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    Tab* TabItemAdapter::makeControl() const {
        return nullptr;// ghnew Tab(ghnew TextTabLayout(theme));
    }

    void TabItemAdapter::bind(Tab& tabView, TabItem* const& tab, size_t position) const {
        //tabView.Layout->SelectableView->Selected = tabLayout.SelectedPosition == position;
        //tabView.selectableView->clicked += [this, position](Control& sender, const MouseClickedEventArgs& args) {
            //tabLayout.SelectedPosition = position;
          //  return true;
        //};
    }
}