#include "ghuipch.h"
#include "Space.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Type& Space::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Space>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Space))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
