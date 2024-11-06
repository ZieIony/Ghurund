#include "ghuipch.h"
#include "TreeView.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& TreeView::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TreeView>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
