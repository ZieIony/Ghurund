#include "ghuipch.h"
#include "TabContainer.h"

#include "TabItemAdapter.h"

namespace Ghurund::UI {
    TabContainer::TabContainer(){
    }
    
    TabContainer::~TabContainer() {
        tabs.deleteItems();
    }
}
