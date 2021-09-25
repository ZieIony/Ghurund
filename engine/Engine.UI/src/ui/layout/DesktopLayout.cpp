#include "ghuipch.h"
#include "DesktopLayout.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& DesktopLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<DesktopLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<DesktopLayout>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(DesktopLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
