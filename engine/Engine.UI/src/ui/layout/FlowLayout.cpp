#include "ghuipch.h"
#include "FlowLayout.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& FlowLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<FlowLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<FlowLayout>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(FlowLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
