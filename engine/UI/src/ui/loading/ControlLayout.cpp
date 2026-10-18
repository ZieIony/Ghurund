#include "ghuipch.h"
#include "ControlLayout.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ControlLayout::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ControlLayout>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
