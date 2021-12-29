#include "ghcdxpch.h"
#include "DisplayMode.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core::DirectX {
    const Ghurund::Core::Type& DisplayMode::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DisplayMode>(Ghurund::Core::DirectX::NAMESPACE_NAME, GH_STRINGIFY(DisplayMode))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
