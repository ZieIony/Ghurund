#include "ghuipch.h"
#include "ExpandableContainer.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ExpandableContainer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ExpandableContainer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}