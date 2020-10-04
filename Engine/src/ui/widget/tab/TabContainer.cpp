#include "TabContainer.h"

namespace Ghurund::UI {
    TabContainer::TabContainer(StyleWithLayout<TabContainer, TabContainerLayout>* style):Widget<TabContainer, TabContainerLayout>(style) {
        Layout.TabContainer->Items = ghnew ListItemSource<TabItem*>(tabs);
    }
    
    TabContainer::~TabContainer() {
        tabs.deleteItems();
    }
}
