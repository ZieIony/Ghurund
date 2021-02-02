#include "ToolbarLayout.h"

#include "ui/adapter/AdapterChildrenProvider.h"

namespace Ghurund::UI {
    void ToolbarLayout::init() {
        recyclerView = ghnew Ghurund::UI::RecyclerView();
        recyclerView->PreferredSize.height = PreferredSize::Height::WRAP;
        recyclerView->LayoutManager = ghnew HorizontalLayoutManager();
        Root = recyclerView;
    }
}
