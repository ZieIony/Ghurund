#include "ghuipch.h"
#include "ManualLayout.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ManualLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ManualLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ManualLayout>(NAMESPACE_NAME, GH_STRINGIFY(ManualLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
