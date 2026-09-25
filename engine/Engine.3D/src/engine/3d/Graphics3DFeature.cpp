#include "ghe3dpch.h"
#include "Graphics3DFeature.h"

namespace Ghurund::Engine::_3D {
    const Ghurund::Core::Type& Graphics3DFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Graphics3DFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
