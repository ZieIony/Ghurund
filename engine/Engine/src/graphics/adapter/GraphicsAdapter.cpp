#include "ghpch.h"
#include "GraphicsAdapter.h"

namespace Ghurund {
    const Ghurund::Core::Type& GraphicsAdapter::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GraphicsAdapter>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(GraphicsAdapter))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
