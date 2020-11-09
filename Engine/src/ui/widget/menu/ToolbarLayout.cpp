#include "ToolbarLayout.h"

namespace Ghurund::UI {
    void ToolbarLayout::init() {
        adapterView = ghnew Ghurund::UI::AdapterView<MenuItem*>();
        adapterView->PreferredSize.height = PreferredSize::Height::WRAP;
        adapterView->LayoutManager = ghnew HorizontalLayoutManager<MenuItem*, Control>();
        adapterView->Adapters.add(ghnew ButtonToolbarAdapter(theme));
        adapterView->Adapters.add(ghnew SeparatorToolbarAdapter(theme));
        root = adapterView;
    }
}
