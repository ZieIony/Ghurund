#include "TabContainer.h"

#include "TabItemAdapter.h"

namespace Ghurund::UI {
    TabContainer::TabContainer(){
        PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
    }
    
    TabContainer::~TabContainer() {
        tabs.deleteItems();
    }
}
