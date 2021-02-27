#include "GraphicsAdapter.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    const Ghurund::Type& GraphicsAdapter::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Adapter))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
