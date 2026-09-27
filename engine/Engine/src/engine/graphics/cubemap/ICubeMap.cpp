#include "ghepch.h"
#include "ICubeMap.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& ICubeMap::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<ICubeMap>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
