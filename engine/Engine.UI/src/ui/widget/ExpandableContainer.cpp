#include "ghuipch.h"
#include "ExpandableContainer.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ExpandableContainer::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ExpandableContainer>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ExpandableContainer>(NAMESPACE_NAME, GH_STRINGIFY(ExpandableContainer))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}