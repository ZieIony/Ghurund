#include "ghepch.h"
#include "ShaderCode.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& ShaderCode::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ShaderCode>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}