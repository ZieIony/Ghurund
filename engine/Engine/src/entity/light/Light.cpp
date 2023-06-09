#include "ghpch.h"

#include "Light.h"

#include "Ghurund.Engine.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& Light::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Light>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Light>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Light))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
