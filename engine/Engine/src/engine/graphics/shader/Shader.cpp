#include "ghepch.h"
#include "Shader.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Shader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Shader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}