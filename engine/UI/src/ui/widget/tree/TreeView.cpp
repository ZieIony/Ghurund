#include "ghuipch.h"
#include "TreeView.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& TreeView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<TreeView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<TreeView>(NAMESPACE_NAME, GH_STRINGIFY(TreeView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
