#include "Light.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Core::Type& Light::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Light>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Light>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Light))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
