#include "ghcpch.h"
#include "Layer.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    const Type& Layer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Layer>(Ghurund::Core::NAMESPACE_NAME, GH_STRINGIFY(Layer))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
