#include "ManualLayout.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Type& ManualLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ManualLayout>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ManualLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
