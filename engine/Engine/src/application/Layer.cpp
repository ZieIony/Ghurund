#include "ghpch.h"
#include "Layer.h"

namespace Ghurund {
    const Ghurund::Core::Type& Layer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Layer>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Layer))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
