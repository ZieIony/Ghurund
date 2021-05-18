#include "ghpch.h"
#include "DisplayMode.h"

namespace Ghurund {
    const Ghurund::Type& DisplayMode::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(DisplayMode))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
