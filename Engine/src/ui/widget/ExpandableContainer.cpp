#include "ghpch.h"
#include "ExpandableContainer.h"

namespace Ghurund::UI {
    const Ghurund::Type& ExpandableContainer::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ExpandableContainer>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ExpandableContainer))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}