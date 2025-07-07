#include "ghepch.h"
#include "IShader.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& IShader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<IShader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}