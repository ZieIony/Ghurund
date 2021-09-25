#include "ghuipch.h"
#include "Space.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Space::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Space>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Space>(NAMESPACE_NAME, GH_STRINGIFY(Space))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
