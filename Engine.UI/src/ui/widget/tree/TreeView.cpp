#include "ghuipch.h"
#include "TreeView.h"

namespace Ghurund::UI {
    const Ghurund::Type& TreeView::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<TreeView>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TreeView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
