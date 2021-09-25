#include "ghpch.h"
#include "DisplayMode.h"

namespace Ghurund {
    const Ghurund::Core::Type& DisplayMode::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DisplayMode>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(DisplayMode))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
