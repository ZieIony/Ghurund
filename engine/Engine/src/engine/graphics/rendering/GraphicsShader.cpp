#include "ghepch.h"
#include "GraphicsShader.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& GraphicsShader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GraphicsShader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
