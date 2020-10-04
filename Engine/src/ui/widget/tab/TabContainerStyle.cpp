#include "TabContainerStyle.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    TabContainerStyle::TabContainerStyle(Theme& theme):StyleWithLayout<TabContainer, TabContainerLayout>(theme) {}
    
    void TabContainerStyle::apply(TabContainer& tabLayout) const {
        __super::apply(tabLayout);
        tabLayout.PreferredSize.width = PreferredSize::Width::FILL;
        tabLayout.PreferredSize.height = PreferredSize::Height::FILL;
        ((TabContainerVerticalBottomLayout&)tabLayout.Layout).Separator->PreferredSize.height = 2;
        ((TabContainerVerticalBottomLayout&)tabLayout.Layout).Separator->Color = theme.getColorAccent();
    }
}

