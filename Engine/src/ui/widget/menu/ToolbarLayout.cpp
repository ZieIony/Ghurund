#include "ToolbarLayout.h"

namespace Ghurund::UI {
    void ToolbarLayout::init() {
        recyclerView = ghnew Ghurund::UI::RecyclerView<MenuItem*>();
        recyclerView->PreferredSize.height = PreferredSize::Height::WRAP;
        recyclerView->LayoutManager = ghnew HorizontalLayoutManager();
        recyclerView->Adapters.add(ghnew ButtonToolbarAdapter());
        recyclerView->Adapters.add(ghnew SeparatorToolbarAdapter(theme));
        root = recyclerView;
    }
}
