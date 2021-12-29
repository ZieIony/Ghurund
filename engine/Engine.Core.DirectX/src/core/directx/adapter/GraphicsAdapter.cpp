#include "ghcdxpch.h"
#include "GraphicsAdapter.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core::DirectX {
    const Ghurund::Core::Type& GraphicsAdapter::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GraphicsAdapter>(Ghurund::Core::DirectX::NAMESPACE_NAME, GH_STRINGIFY(GraphicsAdapter))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
