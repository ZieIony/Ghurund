#include "ghe3dpch.h"
#include "Light.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::_3D {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& Light::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Light>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
