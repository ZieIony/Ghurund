#include "TabContainerLayout.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void TabContainerVerticalBottomLayout::init() {
        VerticalLayout* column = ghnew VerticalLayout();
        container = ghnew ControlContainer();
        container->PreferredSize.width = PreferredSize::Width::FILL;
        container->PreferredSize.height = PreferredSize::Height::FILL;
        separator = ghnew ColorView();
        separator->PreferredSize.height = 2;
        separator->Color = theme.getColorAccent();
        tabContainer = ghnew RecyclerView<TabItem*, Tab>();
        tabContainer->PreferredSize.height = PreferredSize::Height::WRAP;
        tabContainer->LayoutManager = ghnew HorizontalLayoutManager();
        column->Children = { container, separator, tabContainer };
        root = column;
    }
}
