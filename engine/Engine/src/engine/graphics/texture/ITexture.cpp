#include "ghepch.h"
#include "ITexture.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& ITexture::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<ITexture>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}