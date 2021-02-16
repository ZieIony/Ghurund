#include "TabContainerLayout.h"

#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/layout/LinearLayout.h"

namespace Ghurund::UI {
    TabContainerVerticalBottomLayout::TabContainerVerticalBottomLayout(Theme& theme):theme(theme) {
        VerticalLayout* column = ghnew VerticalLayout();
        container = ghnew ControlContainer();
        container->PreferredSize.width = PreferredSize::Width::FILL;
        container->PreferredSize.height = PreferredSize::Height::FILL;
        separator = ghnew ColorView();
        separator->PreferredSize.height = 2;
        separator->Color = theme.Colors[Theme::COLOR_ACCENT];
        tabContainer = ghnew RecyclerView();
        tabContainer->PreferredSize.height = PreferredSize::Height::WRAP;
        tabContainer->LayoutManager = ghnew HorizontalLayoutManager();
        column->Children = { container, separator, tabContainer };
        Root = column;
    }
}