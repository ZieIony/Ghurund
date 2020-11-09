#include "TabContainer.h"

namespace Ghurund::UI {
    TabContainer::TabContainer(TabContainerLayout* layout):Widget(layout) {
        Layout.TabContainer->Items = ghnew ListItemSource<TabItem*>(tabs);
        PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
    }
    
    TabContainer::~TabContainer() {
        tabs.deleteItems();
    }
}
