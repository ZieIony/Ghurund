#include "ghepch.h"
#include "ComputeShader.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& ComputeShader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ComputeShader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
