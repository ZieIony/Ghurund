#include "TabContainer.h"

#include "TabItemAdapter.h"

namespace Ghurund::UI {
    TabContainer::TabContainer(TabContainerLayout* layout):Widget(layout) {
        provider = ghnew AdapterChildrenProvider<TabItem*, Tab>(*layout->TabContainer);
        provider->Items = ghnew ListItemSource<TabItem*>(tabs);
        Layout->TabContainer->childrenProvider = provider;
        PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
    }
    
    TabContainer::~TabContainer() {
        tabs.deleteItems();
    }
}
